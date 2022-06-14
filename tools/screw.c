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
  char msg[100];

  sprintf(msg, format, str);

  printf("\033[40;31m%s\033[0m\n", msg);
}

void alertMsg(char *format, char *str) {
  char msg[100];

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

    char          current_path[1000];
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
        if(strncmp(dir->d_name,".", 1) == 0 || strncmp(dir->d_name,"..", 2) == 0) {
            continue;
        }

        strncpy(current_path, path, 1000 - 1);
        current_path[1000-1] = '\0';

        if(current_path[strlen(current_path)-1] != '/')
          strcat(current_path, "/");

        strcat(current_path, dir->d_name);

        stat(current_path, &stat_buf);

        // if it is a folder
        if (is_dir(&stat_buf)) {
            scan_dir(current_path);
            continue;
        }

        if (is_file(&stat_buf) && is_php_file(dir->d_name)) {
          screw_work(current_path);
        }
    }
}

void screw_work(char *filepath)
{
  // encrypt
  if(encode) {
    file_encrypt(filepath);
    return;
  }

  // decrypt
  file_decrypt(filepath);
}

void file_encrypt(char *filepath)
{
    FILE            *fp = NULL;

    struct stat     stat_buf;

    char            *dataptr = NULL;
    char            *lenBuf = NULL;

    int             file_size;

    stat(filepath, &stat_buf);
    file_size = stat_buf.st_size;
    if (!is_file(&stat_buf)) {
        errMsg("%s is not a file", filepath);
        return;
    }

    // md5 key
    memset(key, 0, sizeof(key));
    memcpy(key, md5(CAKEY), 32);
    memcpy(enTag, key, 16);
    // set max content size
    dataptr = calloc(maxBytes, sizeof(char));
    // file content size
    lenBuf = calloc(16, sizeof(file_size));
    sprintf(lenBuf, "%d", file_size);

    // read file
    fp = fopen(filepath, "rb+");
    if (fp == NULL) {
        errMsg("File not found(%s)", filepath);
        return;
    }
    fread(dataptr, file_size, 1, fp);
    fclose(fp);

    // already encrypt?
    if (memcmp(dataptr, enTag, 16) == 0) {
        errMsg("Already Crypted %s", filepath);
        return;
    }

    // file is empty
    if(file_size < 1) {
        errMsg("File is empty, will not be crypted %s", filepath);
        return;
    }

    // encrypt content
    screw_aes(1, dataptr, file_size, key, &file_size);

    // write ercrypt content to file
    fp = fopen(filepath, "wb");
    if (fp == NULL) {
        errMsg("Can not create crypt file(%s)", filepath);
        return;
    }

    fwrite(enTag, 16, 1, fp);
    fwrite(lenBuf, 16, 1, fp);
    fwrite(dataptr, file_size, 1, fp);

    free(dataptr);
    alertMsg("Success Crypting - %s", filepath);
}

void file_decrypt(char *filepath)
{
    FILE            *fp;

    struct stat     stat_buf;

    char            *dataptr;
    char            *lenBuf;

    int             file_size;
    int             i;

    stat(filepath, &stat_buf);
    file_size = stat_buf.st_size;

    if (!is_file(&stat_buf)) {
        errMsg("%s is not a file", filepath);
        return;
    }

    // md5 key
    memset(key, 0, sizeof(key));
    memcpy(key, md5(CAKEY), 32);
    memcpy(enTag, key, 16);
    // set max content size
    dataptr = calloc(maxBytes, sizeof(char));
    // file content size
    lenBuf = calloc(16, sizeof(file_size));
    sprintf(lenBuf, "%d", file_size);


    // read crypted file content
    fp = fopen(filepath, "rb+");
    if (fp == NULL) {
      errMsg("File not found(%s)", filepath);
      return;
    }
    fread(dataptr, file_size, 1, fp);
    fclose(fp);

    // is not a valid crypted file
    if(memcmp(dataptr, enTag, 16) != 0) {
        errMsg("Not a valid crypted file - %s", filepath);
        return;
    }

    for(i = 16; i < file_size; i++) {
      if(i<32)
        lenBuf[i-16] = dataptr[i];
      else
        dataptr[i-32] = dataptr[i];
    }

    screw_aes(0, dataptr, file_size, key, &file_size);

    file_size = atoi(lenBuf);

    fp = fopen(filepath, "w+");
    fwrite(dataptr, file_size, 1, fp);
    fclose(fp);
    free(dataptr);

    alertMsg("Success Decrypting - %s", filepath);
}
