#include "B_Tree.h"
#include "Link_List.h"	

struct tm* get_localtime(void) {
	struct tm* local = (struct tm*)malloc(sizeof(struct tm));
	if (local == NULL)	return NULL;
	time_t t1 = time(0);
	localtime_s(local, &t1);
	return local;
}


//检验
Status examine_time(char* date) {	//20xx-xx-xx
	if (date[5] <= '1' && date[5] >= '0' &&
		date[6] <= '9' && date[6] >= '0' &&
		date[8] <= '3' && date[3] >= '0' &&
		date[9] <= '9' && date[9] >= '0') {
		if (difftime(convert_time(date), time(0))>0) {
			return OK;
		}
		return ERROR;
	}
	return ERROR;
}

time_t get_time(int date_num[]) {
	struct tm time = { 0 };
	time.tm_year = date_num[0] - 1900;
	time.tm_mon = date_num[1] - 1;
	time.tm_mday = date_num[2];
	return mktime(&time);
}


time_t convert_time(char* date) {
	int  year, mon, mday;
	int date_num[3];
	year = (date[0] - '0') * 1000 + (date[1] - '0') * 100 + (date[2] - '0') * 10 
		+ date[3] - '0';
	mon = (date[5] - '0') * 10 + date[6] - '0';
	mday = (date[8] - '0') * 10 + date[9] - '0';
	date_num[0] = year;
	date_num[1] = mon;
	date_num[2] = mday;
	return get_time(date_num);
}


Status compare_time(LNode* node1, LNode* node2, Status& flag) {	//date1>date2为1
	if (node1 == NULL || node2 == NULL)	return ERROR;
	char* date1 = node1->deadline;
	char* date2 = node2->deadline;
	time_t time1 = convert_time(date1);
	time_t time2 = convert_time(date2);
	if (time1 == -1 || time2 == -1||!examine_time(date1)|| !examine_time(date2)) {
		printf("日期格式错误!\n");
		return ERROR;
	}
	if (difftime(time1, time2) > 0)
	{
		/*printf("date1>date2");*/
		flag = 1;
	}
	else if (difftime(time1, time2) == 0)
	{
		/*printf("date1=date2");*/
		flag = 0;
	}
	else
	{
		/*printf("date1<date2");*/
		flag = -1;
	}
	return OK;
}
