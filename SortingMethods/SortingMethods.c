#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "math.h"

void bubble(int* a, int n) {
	int tmp;
	for (int k = 0; k < n - 1; k++) { //  для точного получения результата надо n-1 перестановка
		for (int i = 0; i < n - 1; i++) { // пробегаем по массиву
			if (a[i] > a[i + 1]) { // меняем местами элементы
				tmp = a[i];
				a[i] = a[i + 1];
				a[i + 1] = tmp;
			}
		}
	}
}
void bubble1(int* a, int n) { // каждый раз на 1 элемент меньше
	int tmp;
	for (int k = 0; k < n - 1; k++) { // вроде для точногополучения результата надо n-1 перестановка
		for (int i = 0; i < n - 1 - k; i++) { // теперь после каждого пробега мы учитываем, что последнее число отсортированно,\
											   и его не надо сравнивать			
			if (a[i] > a[i + 1]) { // например 2 1, надо поменять местами
				tmp = a[i];
				a[i] = a[i + 1];
				a[i + 1] = tmp;
			}
		}
	}

}

void bubble2(int* a, int n) { // остановка, если нет обменов
	int tmp;
	int flag; // флаг для выхода из цикла, если не было перестановок, что значит отсортированность массива
	for (int k = 0; k < n - 1; k++) { // вроде для точногополучения результата надо n-1 перестановка
		flag = 0;
		for (int i = 0; i < n - 1 - k; i++) { 
			if (a[i] > a[i + 1]) { // например 2 1, надо поменять местами
				tmp = a[i];
				a[i] = a[i + 1];
				a[i + 1] = tmp;
				flag = 1;
			}
		}
		if (flag == 0) {
			break;
		}
	}

}

void shaker(int* a, int n) {
	int tmp;
	int flag = 0;
	int l = 0;
	int r = n-1;
	while (1) {
		if (l >= r) break;
		for (int i = l; i < r; i++) { // прямой ход, справа выплывает наибольший элемент
				if (a[i] > a[i + 1]) { 
					tmp = a[i];
					a[i] = a[i + 1];
					a[i + 1] = tmp;
					flag = 1;
				}
		}
		if (flag == 0) {
				break;
		}
		r--;
		for (int i = r; i > l; i--) { // прямой ход, слева выплывает наименьший элемент
			if (a[i] < a[i - 1]) {
				tmp = a[i];
				a[i] = a[i - 1];
				a[i - 1] = tmp;
				flag = 1;
			}
		}
		if (flag == 0) {
			break;
		}
		l++;
	}

}

void SelectionSortExchange(int array[], int size) {
	int minPosition = 0, tmp = 0, m = 0;
	for (int i = 0; i < size; i++) {
		minPosition = i;
for (int j = i + 1; j < size; j++) {
	if (array[minPosition] > array[j]) {
		minPosition = j;
	}
}
for (int counter = 0; counter < minPosition - i; counter++) {
	tmp = array[i];
	for (int k = i; k < size; k++) {
		array[k] = array[k + 1];
	}
	array[size - 1] = tmp;
}
	}
}
void SelectionSortShift(int* a, int n) {
	int tmp;
	int minPosition;
	for (int i = 0; i < n; i++) {
		minPosition = i;
		for (int j = i + 1; j < n; j++) {
			if (a[minPosition] > a[j]) {
				minPosition = j;
			}
		}
		tmp = a[minPosition];
		for (int k = minPosition; k > i; k--) {
			a[k] = a[k - 1];
		}
		a[i] = tmp;
	}
}

void insertion(int* a, int n) {
	int index;
	int tmp;
	for (int i = 1; i < n; i++) { // первый элемент - это уже сортированный массив
		index = i; //индекс, в котором лежит следующий рассматриваемый элемент
		for (int k = i; k > 0; k--) { // пробегаемся по отсортированному массиву справа налево
			if (a[i] < a[k - 1]) { // если рассматриваемый элемент меньше, то смещаем его индекс влево
				index = k - 1;
			}
			else {
				break; // если рассматриваемый элемент больше какого-то из сортированной части, то дальше можно не рассматривать
			}
		}
		tmp = a[i]; // алгоритм сдвига 
		for (int j = i; j > index; j--) {
			a[j] = a[j - 1];
		}
		a[index] = tmp;
	}
}
void binary_insert(int* a, int n) {
	int index;
	int tmp;
	int l, r;
	int mid;
	for (int i = 1; i < n; i++) { // первый элемент - это уже сортированный массив
		index = i; //индекс, в котором лежит следующий рассматриваемый элемент
		r = i - 1; // правая граница
		l = 0; // левая граница
		while (l <= r) { // алгоритм бинарного поиска
			mid = (r + l) / 2;
			if (a[i] < a[mid]) {
				r = mid - 1;
				index = mid; //Если рассматриваемый элемент меньше кагого-то в соритрованной части, то запоминаем индекс
			}
			else {
				l = mid + 1;
			}
		}
		tmp = a[i]; // алгоритм сдвига 
		for (int j = i; j > index; j--) {
			a[j] = a[j - 1];
		}
		a[index] = tmp;
	}

}

void comb(int* a, int n) {
	int delta = n;
	int tmp;
	while (delta = (int)(delta / 1.3)) {
		for (int i = 0; i + delta < n; i++) {
			if (a[i] > a[i + delta]) {
				tmp = a[i];
				a[i] = a[i + delta];
				a[i + delta] = tmp;
			}
		}
	}
}

void merge_sort(int* a, int n) {
	if (n <= 1) return;
	int mid = n / 2;
	int* left = malloc(mid * sizeof(int));
	int* right = malloc((n-mid)  * sizeof(int));
	for (int i = 0; i < mid ; i++) {
		left[i] = a[i];
	}
	for (int i = 0; i < n-mid; i++) {
		right[i] = a[i+ mid];
	}
	merge_sort(left, mid);
	merge_sort(right, n-mid);

	int i = 0; int k = 0; // функция слияния
	while (i < mid  && k < n - mid) {
		if (left[i] <= right[k]) {
			a[i + k] = left[i];
			i++;
		}
		else {
			a[i + k] = right[k];
			k++;
		}
	}
	while (i < mid ) {
		a[i + k] = left[i];
		i++;
	}
	while (k < n - mid) {
		a[i + k] = right[k];
		k++;
	}
	free(left);
	free(right);
	// надо n*log(n) памяти((
}

void merge(int* left, int* right, int len, int len2, int* temp) {
	int p = 0; int k = 0;   // функция слияния
	while (p < len && k < len2) {
		if (left[p] <= right[k]) {
			temp[k + p] = left[p];
			p++;
		}
		else {
			temp[k + p] = right[k];
			k++;
		}
	}
	while (p < len) {
		temp[k + p] = left[p];
		p++;
	}
	while (k < len2) {
		temp[k + p] = right[k];
		k++;
	}
}


void my_merge_sort_alt(int* a, int n) {
	int* temp = malloc(sizeof(int) * n);
	int len = 1; // длина подмассива
	while (len < n) {
		int i = 0; // индекс первого элемента пары
		while (i < n - len) { // пара подмассивов содержит либо 2*len элементов либо len + (1<=x<len) элементов
			int len2 = len; // len2 - длина 2 части
			if (i + len + len2 > n) {
				len2 = n - (i + len);
			}
			merge(a + i, a + len + i, len, len2, temp + i);			
			i += len + len2;
		}
		if (i < n) {
			for (int k = i; k < n; k++) {
				temp[k] = a[k];
			}
		}
		len *= 2;
		for (int k = 0; k < n; k++) {
			  a[k]=temp[k];
		}
	}
}


#define swap(a,b){int t = a; a = b; b = t;}


void heap(int* a, int n) {
	for (int unsorted = n; unsorted > 0; unsorted--) {
		for (int k = unsorted / 2 - 1; k >= 0; k--) {
			if (k * 2 + 2 < unsorted && a[k * 2 + 2] > a[k * 2 + 1] && a[k * 2 + 2] > a[k]) {
				swap(a[k * 2 + 2], a[k]);
			}
			else if (a[k * 2 + 1] > a[k]) {
				swap(a[k * 2 + 1], a[k]);
			}
		}
		swap(a[0], a[unsorted - 1]);
	}
}

void heapify(int* a, int n, int start_index) {
	int i = start_index;
	while (i < n / 2) {
		if (i * 2 + 2 < n && a[i * 2 + 2] > a[i * 2 + 1] && a[i * 2 + 2] > a[i]) {
			swap(a[i * 2 + 2], a[i]);
			i = i * 2 + 2;
		}
		else if (a[i * 2 + 1] > a[i]) {
			swap(a[i * 2 + 1], a[i]);
			i = i * 2 + 1;
		}
		else {
			break;
		}
	}
}
void my_heap_up_down(int* a, int n) {
	for (int i = n / 2 - 1; i >= 0; i--) {
		heapify(a, n, i);		
	}
	for (int i = 1; i < n; i++) {
		swap(a[0], a[n - i]);
		heapify(a, n - i, 0);
	}
}

void simple_count_sort(int* a, int n, int max) { // промежуток значений - от 0 до max
	max = 2;
	int* tmp = calloc(max+1 , sizeof(int));
	int k = 0;
	int old_k;
	for (int i = 0; i < n; i++) {
		tmp[a[i]]++;	
	}
	for (int i = 0; i <= max; i++) {
		old_k = k;
		for (; k < tmp[i] + old_k; k++) {
			a[k] = i;
		}
	}
}

void key_count_sort(int* a, int n, int max) {
	int* tmp = calloc(max + 1, sizeof(int));
	int* ind_arr = calloc(max + 1, sizeof(int));
	for (int i = 0; i < n; i++) { // Подсчет различных значений
		tmp[a[i]]++;
	}

	for (int i = 1; i <= max; i++) { // составим массив индексов
		ind_arr[i] = ind_arr[i - 1] + tmp[i - 1];
	}

	free(tmp);
	int* res = malloc(n * sizeof(int));

	for (int i = 0; i < n; i++) { // результат
		res[ind_arr[a[i]]] = a[i];// например, встретили a[i] = 0; ind_arr[a[i]] = ind_arr[0] = 0,  res[ind_arr[a[i]]] = res[0] = 0, ind_arr[0]++. \
		потом встретили еще раз с другим i a[i] = 0, тк мы сделали ind_arr[0]++, то ind_arr[0] = 1, res[ind_arr[a[i]]] = res[1] = 0 - таким образом правильно составили \
		сортированный массив. 
		ind_arr[a[i]]++;
	}
	
	for (int i = 0; i < n; i++) { // копирование результата в исходный массив
		a[i] = res[i];
	}
	free(ind_arr); free(res);
}

void key_count_sort_left_to_tight(int* a, int n, int max) {
	int* ind_arr = calloc(max + 1, sizeof(int));
	for (int i = 0; i < n; i++) { // Подсчет различных значений
		ind_arr[a[i]]++;
	}

	for (int i = 1; i <= max; i++) { // составим массив индексов
		ind_arr[i] +=  ind_arr[i - 1];
	}
	int* res = malloc(n * sizeof(int));

	for (int i = n-1; i >= 0; i--) { // результат
		res[ind_arr[a[i]]-1] = a[i]; // -1 тк ind_arr указыает индекс элемента на 1 больше
		ind_arr[a[i]]--;
	}

	for (int i = 0; i < n; i++) { // копирование результата в исходный массив
		a[i] = res[i];
	}
	free(ind_arr); free(res);
}

void key_count_sort_left_to_tight_for_radix(int* a, int n, int max, int* init) {
	int* ind_arr = calloc(max + 1, sizeof(int));
	int* new_arr = malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) { // Подсчет различных значений
		ind_arr[a[i]]++;
	}

	for (int i = 1; i <= max; i++) { // составим массив индексов
		ind_arr[i] += ind_arr[i - 1];
	}
	int* res = malloc(n * sizeof(int));

	for (int i = n - 1; i >= 0; i--) { // результат
		res[ind_arr[a[i]] - 1] = a[i]; // -1 тк ind_arr указыает индекс элемента на 1 больше
		new_arr[ind_arr[a[i]] - 1] = init[i];
		ind_arr[a[i]]--;
	}
	for (int i = 0; i < n; i++) { // копирование результата в исходный массив
		init[i] = new_arr[i];
	}
	free(ind_arr); free(res); free(new_arr);
}

void radix_sort(int* a, int n) {
	int rank = 10; // основание системы счисления 
	int d=0; // количество разрядов
	int max = a[0];
	int* tmp_arr = malloc(n * sizeof(int));
	for (int i = 1; i < n; i++) {
		if (a[i] > max) max = a[i];
	}
	while (max > 0) {
		max /= rank;
		d++;
	}
	for (int k = 0; k < d; k++) {
		for (int i = 0; i < n; i++) { // вариант сортировки начиная с первых(правых) разрядов( с младшего разряда)
			tmp_arr[i] = (a[i] / (int)pow(rank, k)) % rank;
			//printf("%i  ", tmp_arr[i]);
			
		}
		key_count_sort_left_to_tight_for_radix(tmp_arr, n, rank - 1, a);
	}

}



void key_count_sort_left_to_tight_for_bucket(int* a, int n, int k, double* init) {
	//a[i] - массив промежутков
	int* ind_arr = calloc(k, sizeof(int));
	double* new_arr = malloc(n * sizeof(double));

	for (int i = 0; i < n; i++) { // Подсчет различных значений
		ind_arr[a[i]]++;
		
	}

	for (int i = 1; i < k; i++) { // составим массив индексов
		ind_arr[i] += ind_arr[i - 1];
	}
	int* res = malloc(n * sizeof(int));

	for (int i = n - 1; i >= 0; i--) { // результат
		new_arr[ind_arr[a[i]] - 1] = init[i];
		ind_arr[a[i]]--;
	}
	for (int i = 0; i < n; i++) { // копирование результата в исходный массив
		init[i] = new_arr[i];
		printf("%lf  ", init[i]);
	}
	puts("");
	free(ind_arr); free(res); free(new_arr);
}


void bucket_sort(double* a, int n, double min, double max) {	
	int k = (int)sqrt(max - min) + 1; // количество промежутков
	int* bucket_arr = malloc(n * sizeof(double));
	double delta = (max - min) / k; // длина промежутка
	int c; // счетчик для нахождения промежутка, которому соответсвтует число
	
	for (int i = 0; i < n; i++) { // нахождение промежутка для элемента
		c = 1;
		while (1) {
			if (a[i] < delta * c) {
				bucket_arr[i] = c - 1;
				break;
			}
			c++;
		}
	}
	key_count_sort_left_to_tight_for_bucket(bucket_arr, n, k, a);
	int index;
	double tmp;
	for (int i = 1; i < n; i++) {
		index = i;
		for (int k = i - 1; k >= 0; k--) {
			if (a[i] < a[k]) {
				index = k;
			}
			else {
				break;
			}
		}
		tmp = a[i];
		for (int j = i; j > index; j--) {
			a[j] = a[j - 1];
		}
		a[index] = tmp;
	}

}

void shell(int* a, int n) {
	int delta = n / 2 +1;
	int index;
	int tmp;
	while (delta >= 1) {
		for (int k = 0; k < delta; k++) { // для разных подмассивов, k - нулевой элемент для подмассива

			for (int j = k + delta; j < n; j += delta) {
				index = j;
				for (int i = j; i > 0; i -= delta) {
					if (a[j] < a[i-delta]) {
						index = i-delta;
					}
					else {
						break;
					}
					//endind = i;
				}
				tmp = a[j];
				for (int i = j; i > index; i -= delta) {
					a[i] = a[i - delta];
				}
				a[index] = tmp;

				for (int i = 0; i < n; i++) {
					//printf("%i  ", a[i]);
				}

			}
		}
		if (delta == 1) break;
		delta = delta / 2 + 1;
	}
}

void quick_sort(int* a, int n){
	if (n < 2) return;
	int pivot;
	//pivot = a[n-1];
	pivot = a[0];
	swap(a[0], a[n - 1]);
	//printf("%i ", pivot);	
	int w = 0;
	for (int r = 0; r < n-1 ; r++) {
		if (a[r] < pivot) {
			swap(a[w], a[r]);
			w++;
		}
	}
	swap(a[w], a[n-1]);
	quick_sort(a, w);
	quick_sort(a+w+1, n-w-1);
}

void quick_sort_hoar(int* a, int n) {
	if (n < 2) return;
	int l = 0;
	int r = n-2;
	/*int pivot = a[0];
	swap(a[0], a[n - 1]);*/
	int pivot = a[n-1];
	
	while (l <= r) {
		while (a[l] < pivot)
			l++;
		while (r >= 0 && a[r] >= pivot )
			r--;
		if (l < r && (a[l] > pivot) && (a[r] < pivot)) {
			swap(a[l], a[r]);
		}
	}
	swap(a[n - 1], a[l]);
	quick_sort_hoar(a, l);
	quick_sort_hoar(a + l + 1, n - l - 1);
}


void quicksort_lomuto(int* array, int size) {

	if (size < 2) {
		return;
	}

	int pivot = array[size - 1];
	int  w = 0;
	int r = 0;
	while (r < size) {
		if (array[r] < pivot) {
			swap(array[r], array[w]);
			w++;
		}
		r++;
	}

	swap(array[w], array[size - 1]);
	quicksort_lomuto(array, w);
	quicksort_lomuto(array + w + 1, size - w - 1);
}
void quicksort_hoara(int* array, int size) {
	if (size < 2)
		return;

	int l = 0;
	int r = size - 2;

	int pivot = array[size - 1];

	while (l <= r) {
		while (array[l] < pivot)
			l++;
		while ((r >= 0) && array[r] >= pivot)
			r--;

		if ((l < r) && (array[l] >= pivot) && (array[r] < pivot))
			swap(array[l], array[r]);
	}
	swap(array[l], array[size - 1]);

	quicksort_hoara(array, l);
	quicksort_hoara(array + l + 1, size - l - 1);
}
typedef struct node {
	int val;
	struct node* next;
} Node;
typedef struct {
	Node* head;
	int len;
} List;
//List* list_new(int size) {
//	List* list = (List*)malloc(sizeof(List));
//
//	if (size > 0) {
//		/*list->head = (Node*)malloc(sizeof(Node));
//		Node* node = list->head;*/
//		Node* node = (Node*)malloc(sizeof(Node));
//		list->head = node;
//		for (int i = 1; i < size; i++) {
//			node->next = (Node*)malloc(sizeof(Node));
//			node->val = 0;
//			node = node->next;
//		}
//		node->val = 0;
//		node->next = NULL;
//	}
//	list->len = size;
//	return list;
//}

List* list_new() {
	List* list = (List*)malloc(sizeof(List));
	list->head = NULL;
	return list;
}

void add_begin(List* list, int val) {
	Node* node = malloc(sizeof(Node));
	node->next = list->head;
	node->val = val;
	list->head = node;
}
void add_end(List* list, int val) {
	Node* node;
	for ( node = list->head; node->next != NULL; node = node->next);
	node->next = malloc(sizeof(Node));
	node->next->next = NULL;
	node->next->val = val;
}

void print_list(List* list) {
	for (Node* node = list->head; node != NULL; node = node->next) {
		printf("%i  ", node->val);
	}
}

void add_center(List* list, int place, int val) {
	Node* node = list->head;
	for (int i = 0; i < place-1; i++) {
		node = node->next;
	}
	Node* new_n = malloc(sizeof(Node));
	new_n->next = node->next;
	node->next = new_n;
	new_n->val = val;

}
void delete_start(List* list) {
	Node* node;
	node = list->head;
	list->head = list->head->next;
	free(node);
}
void delete_end(List* list) {
	Node* node;
	for (node = list->head; node->next->next != NULL; node = node->next);
	free(node->next);
	node->next = NULL;
}
void delete_center(List* list, int place) {
	Node* node = list->head;
	Node* tmp;
	for (int i = 0; i < place - 1; i++) {
		node = node->next;
	}
	tmp = node->next->next ;
	free(node->next);
	node->next = tmp;
}
void list_demonstrate() {
	List* list = list_new();
	add_begin(list, 15);
	add_end(list, 20);
	add_end(list, 25);
	add_end(list, 30);
	add_end(list, 35);
	print_list(list);
	add_center(list, 2, 228);
	puts("");
	print_list(list);
	delete_start(list);
	puts("");
	print_list(list);
	delete_end(list);
	puts("");
	print_list(list);
	delete_center(list, 1);
	puts("");
	print_list(list);
}
#define static_assert_exp(expression) int array[!!(expression)]

typedef struct  {
	int* buffer;
	int head;
	int size;
}Stack;
Stack* stack_new(int size) {
	Stack* stack = malloc(sizeof(Stack));
	stack->buffer = malloc(size * sizeof(int));
	stack->head = 0;
	stack->size = size;
	return stack;
}
void push(Stack* stack, int val) {
	if (stack->head < stack->size) {
		stack->buffer[stack->head] = val;
		stack->head++;
	}
}
void stack_print(Stack* stack) {
	for (int i = 0; i < stack->head; i++) {
		printf("%i  ", stack->buffer[i]);
	}
}
int* pop(Stack* stack) {
	int val;
	if (stack->head != 0) {
		val = stack->buffer[stack->head - 1];
		stack->head--;
	}
	else {
		return 0;
	}
	return val;
}

typedef struct {
	int* bufffer;
	int head;
	int tail;
	int size;
	int isEmpty;
}Queue;
Queue* queue_init(size) {
	Queue* queue = malloc(sizeof(Queue));
	queue->bufffer = malloc(size * sizeof(int));
	queue->head = 0;
	queue->tail = 0;
	queue-> size = size;
	queue->isEmpty = 1;
	return queue;
}
void QueuePush(Queue* queue, int val) {
	if (queue->isEmpty == 1 || queue->head != queue->tail) {
		queue->bufffer[queue->tail] = val;
		if (queue->tail + 1 < queue->size) {
			queue->tail++;
		}
		else {
			queue->tail = 0;
		}
	}
	queue->isEmpty = 0;
}
void queue_print(Queue* q) {
	if (q->head < q->tail) {
		for (int i = q->head; i < q->tail; i++) {
			printf("%i  ", q->bufffer[i]);
		}
	}
	else if ( q->isEmpty == 1);
	else {
		for (int i = q->head; i < q->size; i++) {
			printf("%i  ", q->bufffer[i]);
		}
		for (int i = 0; i < q->tail; i++) {
			printf("%i  ", q->bufffer[i]);
		}
	}
	puts("");
}
int QueuePop(Queue* queue) {
	int val;
	val = queue->bufffer[queue->head];
	if (queue->head + 1 < queue->size) {
		queue->head++;
	}
	else {
		queue->head = 0;
	}

	return val;
}
#define static_assert(expression) 1/(expression)

double Power(double a, int n) {
	double b = 1.0;
	while (n > 0) {
		if (n % 2 == 1) {
			n--;
			b *= a;
		}
		else {
			a *= a;
			n /= 2;
		}
	}
	return b;
}
int main() {
	//int a[] = { 1, 2, 2, 2,5,6,7,8, 9, 10 };
	//int a[] = {25, 18, 1, 5,2,2,10, 54, 15};
	//int a[] = { 1, 9, 3, 6, 2, 8, 5, 4, 2, 0 };
	//int a[] = {  1,5,4,3,2 };
	//int a[] = { 0,1,2,0,0,2, 1, 0, 1, 2};
	//int a[] = { 125, 18, 1115, 53,72,72,10, 54, 540 };
	//double ad[] = {1.4, 1.3, 1.2, 7.5, 4.0, 3.6, 9.8, 5.3 };
	//int a[] = { 6,4,4,3,2,1};
	int a[] = { 3,6,3,4,7,2,3, 10, 3 };
	int n = 9;
	printf("%lf", Power(2.0, 5));
	union {
		double x;
		int y;
	}myun;
	myun.x = 15;
	/*Queue* q = queue_init();
	QueuePush(q, 14);
	QueuePush(q, 15);
	QueuePush(q, 16);
	QueuePush(q, 17);
	QueuePush(q, 18);
	queue_print(q);
	QueuePop(q);
	queue_print(q);*/
	//static_assert(2<5);
	/*Stack* stack = stack_new(10);
	push(stack, 15);
	push(stack, 16);
	push(stack, 17);
	stack_print(stack);
	puts("");
	pop(stack);
	stack_print(stack);*/
	/*int (*arr)[3] = malloc(3*3*sizeof(int));
	arr[2][2] = 256;
	int* arr_p = arr;*/
	/*int arr[] = { 1,2,3,4 };

	printf("%i  ", *(arr+2));*/
	/*double (*fun)(double);
	fun = cos;
	printf("%lf", fun(1));*/
	//static_assert_exp(5 < 5);


	/*quicksort_hoara(a, n);
	for (int i = 0; i < n; i++) {
		printf("%i  ", a[i]);
	}*/



	return 0;
}