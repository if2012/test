/* If the char "config_file" isn't match with the cgic source pack,modify the 
value to suit your needs.  -- luoyifei */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "cgic.h"

#define BufferLen 1024
#define WEB_UPLOAD_CONFIG_FILE      "/var/webconfigfile.tar.gz"

int cgiMain(void)
{
	cgiFilePtr file;
	int targetFile;
	mode_t mode;
	char name[128];
	char fileNameOnServer[64];
	//char contentType[1024];
	char buffer[BufferLen];
	char *tmpStr=NULL;
	int size;
	int got,t;
	//char cmd[64];

	cgiHeaderContentType("text/html");

	//取得html页面中的file元素的值，应该是文件在客户机上的路径名
	//第一个参数"config_file" 必须与cgic中的attr 值相同，下同
	if (cgiFormFileName("config_file", name, sizeof(name)) !=cgiFormSuccess) {
		//fprintf(stderr,"could not retrieve filename\n");
		printf("could not retrieve filename\n");
		goto FAIL;
	}
	cgiFormFileSize("config_file", &size);
	
	//取得文件类型
	//cgiFormFileContentType("file", contentType, sizeof(contentType));
	
	//目前文件存在于系统临时文件夹中，通常为/tmp，通过该命令打开
	//临时文件。临时文件的名字与用户文件的名字不同，所以不能通过路径
	///tmp/userfilename的方式获得文件
	if (cgiFormFileOpen("config_file", &file) != cgiFormSuccess) {
		fprintf(stderr,"could not open the file\n");
		goto FAIL;
	}
	t=-1;
	//从路径名解析出用户文件名
	while(1){
		tmpStr=strstr(name+t+1,"\\");
		if(NULL==tmpStr)
			tmpStr=strstr(name+t+1,"/");//if "\\" is not path separator, try "/"
		if(NULL!=tmpStr)
			t=(int)(tmpStr-name);
		else
			break;
	}
	strcpy(fileNameOnServer,name+t+1);
	mode=S_IRWXU|S_IRGRP|S_IROTH;
	//在/var目录下建立新的文件，第一个参数实际上是路径名�
	targetFile=open(WEB_UPLOAD_CONFIG_FILE,O_RDWR|O_CREAT|O_TRUNC|O_APPEND,mode);
	if(targetFile<0){
		fprintf(stderr,"could not create the new file,%s\n",fileNameOnServer);
		goto FAIL;
	}
	//从系统临时文件中读出文件内容，并放到刚创建的目标文件中
	while (cgiFormFileRead(file, buffer, BufferLen, &got) ==cgiFormSuccess){
		if(got>0)
			write(targetFile,buffer,got);
	}
	cgiFormFileClose(file);
	close(targetFile);
	goto END;
FAIL:
	fprintf(stderr,"Failed to upload");
	return 1;
END:
	//printf("File \"%s\" has been uploaded",fileNameOnServer);
	//sprintf(cmd, "chmod 777 %s\n", WEB_UPLOAD_CONFIG_FILE);
	//system(cmd);
	return 0;
}
