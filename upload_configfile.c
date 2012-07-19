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

	//È¡µÃhtmlÒ³ÃæÖĞµÄfileÔªËØµÄÖµ£¬Ó¦¸ÃÊÇÎÄ¼şÔÚ¿Í»§»úÉÏµÄÂ·¾¶Ãû
	//µÚÒ»¸ö²ÎÊı"config_file" ±ØĞëÓëcgicÖĞµÄattr ÖµÏàÍ¬£¬ÏÂÍ¬
	if (cgiFormFileName("config_file", name, sizeof(name)) !=cgiFormSuccess) {
		//fprintf(stderr,"could not retrieve filename\n");
		printf("could not retrieve filename\n");
		goto FAIL;
	}
	cgiFormFileSize("config_file", &size);
	
	//È¡µÃÎÄ¼şÀàĞÍ
	//cgiFormFileContentType("file", contentType, sizeof(contentType));
	
	//Ä¿Ç°ÎÄ¼ş´æÔÚÓÚÏµÍ³ÁÙÊ±ÎÄ¼ş¼ĞÖĞ£¬Í¨³£Îª/tmp£¬Í¨¹ı¸ÃÃüÁî´ò¿ª
	//ÁÙÊ±ÎÄ¼ş¡£ÁÙÊ±ÎÄ¼şµÄÃû×ÖÓëÓÃ»§ÎÄ¼şµÄÃû×Ö²»Í¬£¬ËùÒÔ²»ÄÜÍ¨¹ıÂ·¾¶
	///tmp/userfilenameµÄ·½Ê½»ñµÃÎÄ¼ş
	if (cgiFormFileOpen("config_file", &file) != cgiFormSuccess) {
		fprintf(stderr,"could not open the file\n");
		goto FAIL;
	}
	t=-1;
	//´ÓÂ·¾¶Ãû½âÎö³öÓÃ»§ÎÄ¼şÃû
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
	//ÔÚ/varÄ¿Â¼ÏÂ½¨Á¢ĞÂµÄÎÄ¼ş£¬µÚÒ»¸ö²ÎÊıÊµ¼ÊÉÏÊÇÂ·¾¶Ãû£
	targetFile=open(WEB_UPLOAD_CONFIG_FILE,O_RDWR|O_CREAT|O_TRUNC|O_APPEND,mode);
	if(targetFile<0){
		fprintf(stderr,"could not create the new file,%s\n",fileNameOnServer);
		goto FAIL;
	}
	//´ÓÏµÍ³ÁÙÊ±ÎÄ¼şÖĞ¶Á³öÎÄ¼şÄÚÈİ£¬²¢·Åµ½¸Õ´´½¨µÄÄ¿±êÎÄ¼şÖĞ
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
