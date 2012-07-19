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

	//ȡ��htmlҳ���е�fileԪ�ص�ֵ��Ӧ�����ļ��ڿͻ����ϵ�·����
	//��һ������"config_file" ������cgic�е�attr ֵ��ͬ����ͬ
	if (cgiFormFileName("config_file", name, sizeof(name)) !=cgiFormSuccess) {
		//fprintf(stderr,"could not retrieve filename\n");
		printf("could not retrieve filename\n");
		goto FAIL;
	}
	cgiFormFileSize("config_file", &size);
	
	//ȡ���ļ�����
	//cgiFormFileContentType("file", contentType, sizeof(contentType));
	
	//Ŀǰ�ļ�������ϵͳ��ʱ�ļ����У�ͨ��Ϊ/tmp��ͨ���������
	//��ʱ�ļ�����ʱ�ļ����������û��ļ������ֲ�ͬ�����Բ���ͨ��·��
	///tmp/userfilename�ķ�ʽ����ļ�
	if (cgiFormFileOpen("config_file", &file) != cgiFormSuccess) {
		fprintf(stderr,"could not open the file\n");
		goto FAIL;
	}
	t=-1;
	//��·�����������û��ļ���
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
	//��/varĿ¼�½����µ��ļ�����һ������ʵ������·�����
	targetFile=open(WEB_UPLOAD_CONFIG_FILE,O_RDWR|O_CREAT|O_TRUNC|O_APPEND,mode);
	if(targetFile<0){
		fprintf(stderr,"could not create the new file,%s\n",fileNameOnServer);
		goto FAIL;
	}
	//��ϵͳ��ʱ�ļ��ж����ļ����ݣ����ŵ��մ�����Ŀ���ļ���
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
