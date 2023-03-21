#define _CRT_SECURE_NO_WARNINGS
#include <shlwapi.h>
#include <stdio.h>
#include <windows.h>
#pragma comment(lib,"shlwapi.lib") // for PathFindExtensionA
typedef enum {
	C,
	CPP,
	H
}File_type;
typedef struct {
	char* file_name;
	File_type type;
	int file_size;
	int str_quantity;
	int comments_byte;
	double comments_percent;
	double average_str_len;
}Parametrs;
typedef struct {
	int total_size;
	int total_commet_size;
	double total_commet_percent;
	int total_str;
	int c_max_str;
	double c_average_str;
	int cpp_max_str;
	double cpp_average_str;
	int h_max_str;
	double h_average_str;
}Statistics;
int index;
void read_file(char* path, char* name, Parametrs** file_param);
Statistics get_stat(Parametrs* file_param);


int dir_open(char* dir_path, char* dir_name, Parametrs** file_param, int size_of_path, int size_of_name) {
	char* dir_remain = calloc(size_of_path + size_of_name + 3, sizeof(char));
	char* find_files = calloc(size_of_path + size_of_name + 4, sizeof(char));
	strcat(dir_remain, dir_path);
	strcat(dir_remain, dir_name);
	strcat(dir_remain, "\\\\");
	strcat(find_files, dir_remain);
	strcat(find_files, "*");
	WIN32_FIND_DATAA FindFileData;
	HANDLE hf;
	hf = FindFirstFileA(find_files, &FindFileData);
	if (hf == INVALID_HANDLE_VALUE) {
		printf("%s invalid path", find_files);
		return 1;
	}
	do {
		int b = strlen(FindFileData.cFileName);
		if (FindFileData.cFileName[0] == '.') continue;
		if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0) { // if directory          
			dir_open(dir_remain, FindFileData.cFileName, file_param, strlen(dir_remain), strlen(FindFileData.cFileName)); 
		}
		else {
			read_file(dir_remain, FindFileData.cFileName, file_param);
		}

	} while (FindNextFileA(hf, &FindFileData) != 0);
	FindClose(hf);
	free(dir_remain);
	free(find_files);
	return 0;
}
void read_file(char* path, char* name, Parametrs** file_param) {
	static int struct_size = 1;
	 Parametrs* p = (Parametrs*)realloc(*file_param, struct_size * sizeof(Parametrs));
	 if (p == NULL) {
		 puts("realloc error");
		 return;
	 }
	 else {
		 *file_param = p;		
	 }	
	char* file_path = calloc(strlen(path)+strlen(name)+1, sizeof(char));
	if (file_path == NULL) {
		return;
	}
	strcat(file_path, path);
	strcat(file_path, name);
	index = struct_size - 1;
	memset(&(*file_param)[index], 0, sizeof(Parametrs));
	if (strcmp(PathFindExtensionA(file_path), ".c") == 0) {
		(*file_param)[index].type = C;
	}
	else if (strcmp(PathFindExtensionA(file_path), ".cpp") == 0) {
		(*file_param)[index].type = CPP;
	}
	else if (strcmp(PathFindExtensionA(file_path), ".h") == 0) {
		(*file_param)[index].type = H;
	}
	else {
		free(file_path);
		return;
	}
	(*file_param)[index].file_name = calloc(strlen(name)+1, sizeof(char));
	if ((*file_param)[index].file_name == NULL) {
		return;
	}
	strcat((*file_param)[index].file_name, name);
	//(*file_param)[index].comments_byte = -1;
	FILE* file = fopen(file_path, "r");
	if (file == NULL) {
		printf("Error: %s\n", strerror(errno));
		free(file_path);
		return;
	}
	int slash_flag = 0; // for commet //
	int str_flag = 0; // for commet /* */
	char c;
	while (fscanf(file, "%c", &c) == 1)
	{
		if ((*file_param)[index].str_quantity == 0) (*file_param)[index].str_quantity = 1;
		(*file_param)[index].file_size++;
		if (c == '\n') (*file_param)[index].str_quantity++;

		if (str_flag == 2 || str_flag == 3) {
			slash_flag = 0;
		}
		else if (c == '/' && slash_flag != 2) {
			slash_flag++;
			if(slash_flag == 2) (*file_param)[index].comments_byte--;
		}
		else if (slash_flag != 2 || c == '\n') {
			slash_flag = 0;
		}

		if (slash_flag == 2) {
			str_flag = 0;
		}
		else if (c == '/' && str_flag == 0) {
			str_flag = 1;
		}
		else if (c == '*' && str_flag == 1) {
			str_flag = 2;
		}
		else if (c == '*' && str_flag == 2) {
			str_flag = 3;
		}
		else if (c == '/' && str_flag == 3) {
			str_flag = 0;
			(*file_param)[index].comments_byte -= 2;
		}
		else if (c != '/' && str_flag == 3) {
			str_flag = 2;
		}
		else if (str_flag != 2) {
			str_flag = 0;
		}
		

		if (slash_flag == 2 || str_flag == 2 || str_flag == 3) (*file_param)[index].comments_byte++;
	}

	if ((*file_param)[index].str_quantity == 0) {
		(*file_param)[index].average_str_len = (*file_param)[index].file_size;
	}
	else {
		(*file_param)[index].average_str_len = (double)(*file_param)[index].file_size / (double)(*file_param)[index].str_quantity;
	}
	if ((*file_param)[index].file_size == 0) {
		(*file_param)[index].comments_percent = 0;
		(*file_param)[index].comments_byte = 0;
	}
	else {
		/*if ((*file_param)[index].comments_byte == -1) {
			(*file_param)[index].comments_percent = 0;
			(*file_param)[index].comments_byte = 0;
		}*/
		/*else {
			(*file_param)[index].comments_percent = (double)(*file_param)[index].comments_byte / (double)(*file_param)[index].file_size * 100;
		}*/
		//(*file_param)[index].comments_byte++;
		if ((*file_param)[index].comments_byte == 0) {
			(*file_param)[index].comments_percent = 0;
		}
		else {
			(*file_param)[index].comments_percent = (double)(*file_param)[index].comments_byte / (double)(*file_param)[index].file_size * 100;
		}
	}
	fclose(file);
	free(file_path);
	struct_size++;
}
void stat_display(Parametrs* file_param) {
	for (int i = 0; i <= index; i++) {
		printf("%s:", file_param[i].file_name);
		printf("\t size: %i", file_param[i].file_size);
		printf("\t str quantity: %i", file_param[i].str_quantity);
		printf("\t average str size: %.2f", file_param[i].average_str_len);
		printf("\t comments size: %i", file_param[i].comments_byte);
		printf("\t comments %%: %.2f %%\n", file_param[i].comments_percent);
	}
	Statistics s = get_stat(file_param);
	printf("\n%s", "Total statistics:");
	printf("\ttotal size: %i", s.total_size);
	printf("\ttotal comments size: %i", s.total_commet_size);
	printf("\ttotal comments %%: %.2f %%", s.total_commet_percent);
	printf("\ttotal str: %i\n", s.total_str);

	printf("\nGroup .c:\tmax str:%i", s.c_max_str);
	printf("\taverage str: %.2f\n", s.c_average_str);

	printf("Group .cpp:\tmax str:%i", s.cpp_max_str);
	printf("\taverage str: %.2f\n", s.cpp_average_str);

	printf("Group .h:\tmax str:%i", s.h_max_str);
	printf("\taverage str: %.2f\n", s.h_average_str);
}
Statistics get_stat(Parametrs* file_param) {
	Statistics s;
	int c_count = 0;
	int cpp_count = 0;
	int h_count = 0;
	int c_max = 0;
	int c_average = 0;
	int cpp_max = 0;
	int cpp_average = 0;
	int h_max = 0;
	int h_average = 0;
	memset(&s, 0, sizeof(Statistics));
	for (int i = 0; i <= index; i++) {
		s.total_size += file_param[i].file_size;
		s.total_commet_size += file_param[i].comments_byte;
		s.total_str += file_param[i].str_quantity;
		s.total_commet_percent = (double)s.total_commet_size / (double)s.total_size * 100;
		if (file_param[i].type == C) {
			c_count++;
			if (file_param[i].str_quantity > c_max) c_max = file_param[i].str_quantity;
			c_average += file_param[i].str_quantity;
		}
		else if (file_param[i].type == CPP) {
			cpp_count++;
			if (file_param[i].str_quantity > cpp_max) cpp_max = file_param[i].str_quantity;
			cpp_average += file_param[i].str_quantity;
		}
		else {
			h_count++;
			if (file_param[i].str_quantity > h_max) h_max = file_param[i].str_quantity;
			h_average += file_param[i].str_quantity;
		}
	}
	s.c_max_str = c_max;
	if (c_count != 0)s.c_average_str = (double)c_average / (double)c_count;

	s.cpp_max_str = cpp_max;
	if (cpp_count != 0)s.cpp_average_str = (double)cpp_average / (double)cpp_count;

	s.h_max_str = h_max;
	if (h_count != 0)s.h_average_str = (double)h_average / (double)h_count;

	return s;
}
int main(int argc, const char* argv[]) {
	if (argc < 2) {
		puts("help: not enough input arguments");
		return 0;
	}
	else if (argc == 2 && ((!strcmp(argv[1], "/?") || !strcmp(argv[1], "-?")))) {
		puts("help: add catalogs to the command line input");
		return 0;
	}
	Parametrs* file_param = malloc(sizeof(Parametrs));
	for (int k = 1; k < argc; k++) {
		puts(argv[k]);
		if (dir_open(argv[k], "", &file_param, strlen(argv[k]), 0) == 1) return 0;
	}
	puts("");
	stat_display(file_param);
	free(file_param);
	return 0;
}