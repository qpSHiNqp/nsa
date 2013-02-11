#include <stdio.h>
#include <stdlib.h>
#include "common.h"

int usage(char *instruction, char *argv[]) {
	printf(instruction, argv[0]);
	return 0;
}

sockinfo *sockinfo_init() {
	return NULL;
}

sockinfo *sockinfo_delete(sockinfo *arr, sockinfo *target) {
	if(target->prev != NULL)
		target->prev->next = target->next;
	else
		arr = target->next;
	if(target->next != NULL)
		target->next->prev = target->prev;
	free(target);
	return arr;
}

sockinfo *sockinfo_push(sockinfo *arr, sockinfo *target) {
	sockinfo *tmp;
	if (arr == NULL) {
		arr = target;
		target->prev = NULL;
		target->next = NULL;
		return target;
	} else {
		tmp = arr;
		while(tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = target;
		target->prev = tmp;
		target->next = NULL;
		return arr;
	}
}

int sockinfo_length(sockinfo *arr) {
	sockinfo *tmp = arr;
	int ret = 0;
	if (tmp == NULL)
		return ret;
	ret++;

	for(tmp = arr; tmp->next != NULL; tmp = tmp->next)
		ret++;

	return ret;
}

