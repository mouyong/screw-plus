#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <dirent.h>
#include <memory.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../php_screw_plus.h"
#include "../aes.c"
#include "../aes_crypt.c"
#include "../md5.h"

int encode = 1;

uint8_t enTag[16];
uint8_t key[64];

int is_file(struct stat *stat_buf);
int is_dir(struct stat *stat_buf);
int is_php_file(char *filename);

void scan_dir(char *path);
void screw_work(char *file);

void file_encrypt(char *file);
void file_decrypt(char *file);

void errMsg(char *format, char *str) {
    char msg[1000];

    sprintf(msg, format, str);

    printf("\033[40;31m%s\033[0m\n", msg);
}

void alertMsg(char *format, char *str) {
    char msg[1000];

    sprintf(msg, format, str);

    printf("\033[1;32m%s\033[0m\n", msg);
}

void main(int argc, char**argv)
{
    DIR *dirptr;
    FILE *fptr;

    struct stat stat_buf;

    char path[300];
    char suf[1];

    // need input dir path or file path
    if (argc < 2) {
        errMsg("Please input a valid path", "");
        exit(1);
    }

    // -d --decode
    if(argc > 2 && strncmp(argv[2], "-d", 2) == 0) {
        encode = 0;
    }

    // get input path
    strcpy(path, argv[1]);

    // get the path stat info
    stat(path, &stat_buf);

    if (is_dir(&stat_buf)) {
        scan_dir(path);
    }

    if (is_file(&stat_buf)) {
        screw_work(path);
    }
}

int is_file(struct stat *stat_buf)
{
    return S_ISREG(stat_buf->st_mode);
}

int is_dir(struct stat *stat_buf)
{
    return S_ISDIR(stat_buf->st_mode);
}

int is_php_file(char *filename)
{
    int i;
    char tmpS[5];
    char *ext;

    ext = filename;

    memset(tmpS, 0, sizeof(tmpS));

    for(i = 0; i < strlen(filename); i++) {
        if(i >= strlen(filename)-4) {
            tmpS[i - strlen(filename) + 4] = filename[i];
        }
    }

    tmpS[4] = '\0';

    return strncmp(tmpS, ".php", 4) == 0 ? 1 : 0;
}

void scan_dir(char *path)
{
    DIR           *dirptr = NULL;
    FILE          *fp = NULL;

    struct dirent *dir = NULL;
    struct stat   stat_buf;

    int           i = 0;
    int           l = 0;

    printf("current %s\n", path);
    stat(path, &stat_buf);
    if (!is_dir(&stat_buf)) {
        errMsg("%s is not a dir", path);
        return;
    }

    dirptr = opendir(path);
    if(dirptr == NULL) {
        errMsg("cannot open dir %s", path);
        return;
    }

    while (NULL != (dir = readdir(dirptr)))
    {
        if(strncmp(dir->d_name, ".", 1) == 0 || strncmp(dir->d_name, "..", 2) == 0) {
            continue;
        }

        if(!is_php_file(path) && path[strlen(path)-1] != '/') {
            strcat(path, "/");
        }

        l = strlen(path) + strlen(dir->d_name);

        char curPath[l+1];
        memset(curPath, 0, sizeof(curPath));

        strcat(curPath, path);
        strcat(curPath, dir->d_name);

        stat(curPath, &stat_buf);

        // if it is a folder
        if (is_dir(&stat_buf)) {
            scan_dir(curPath);
        } else if (is_file(&stat_buf) && is_php_file(dir->d_name)) {
            screw_work(curPath);
        }
    }
}

void screw_work(char *filepath)
{
    if(encode) {
        // encrypt
        file_encrypt(filepath);
    } else {
        // decrypt
        file_decrypt(filepath);
    }

}

void file_encrypt(char *filepath)
{
    FILE            *fp = NULL;

    struct stat     stat_buf;

    char            *dataptr = NULL;
    char            lenBuf[16];
    int             datalen;

    stat(filepath, &stat_buf);
    datalen = stat_buf.st_size;

    // md5 key
    memset(key, 0, sizeof(key));
    memcpy(key, md5(CAKEY), 32);
    memcpy(enTag, key, 16);
    memset(lenBuf, 0, 16);
    sprintf(lenBuf, "%d", datalen);
    // set max content size
    dataptr = calloc(maxBytes, sizeof(char));

    // read file
    fp = fopen(filepath, "rb");
    if (fp == NULL) {
        errMsg("File not found(%s)", filepath);
        return;
    }
    fread(dataptr, datalen, 1, fp);
    fclose(fp);

    // already encrypt?
    if (memcmp(dataptr, enTag, 16) == 0) {
        errMsg("Already Crypted %s", filepath);
        return;
    }

    // file is empty
    if(datalen < 1) {
        errMsg("File is empty, will not be crypted %s", filepath);
        return;
    }

    // encrypt content
    screw_aes(1, dataptr, datalen, key, &datalen);

    // write ercrypt content to file
    fp = fopen(filepath, "wb");
    if (fp == NULL) {
        errMsg("Can not create crypt file(%s)", filepath);
        return;
    }

    fwrite(enTag, 16, 1, fp);
    fwrite(lenBuf, 16, 1, fp);
    fwrite(dataptr, datalen, 1, fp);
    fclose(fp);
    free(dataptr);

    alertMsg("Success Crypting - %s", filepath);
}

void file_decrypt(char *filepath)
{
    FILE            *fp;

    struct stat     stat_buf;

    char            *dataptr;
    char            lenBuf[16];

    int             i, datalen;

    stat(filepath, &stat_buf);
    datalen = stat_buf.st_size;

    // md5 key
    memset(key, 0, sizeof(key));
    memcpy(key, md5(CAKEY), 32);
    memcpy(enTag, key, 16);
    memset(lenBuf, 0, 16);
    // set max content size
    dataptr = calloc(maxBytes, sizeof(char));

    // read crypted file content
    fp = fopen(filepath, "rb");
    if (fp == NULL) {
        errMsg("File not found(%s)", filepath);
        return;
    }
    fread(dataptr, datalen, 1, fp);
    fclose(fp);

    // is not a valid crypted file
    if(memcmp(dataptr, enTag, 16) != 0) {
        errMsg("Not a valid crypted file - %s", filepath);
        return;
    }

    for(i = 16; i < datalen; i++) {
        if(i < 32) {
            lenBuf[i-16] = dataptr[i];
        } else {
            dataptr[i-32] = dataptr[i];
        }
    }

    screw_aes(0, dataptr, datalen, key, &datalen);

    datalen = atoi(lenBuf);

    fp = fopen(filepath, "w+");
    fwrite(dataptr, datalen, 1, fp);
    fclose(fp);

    free(dataptr);

    alertMsg("Success Decrypting - %s", filepath);
}
