#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 20

//추가적인 공간을 필요로 하기에 추가 공간을 더할 리스트 변수를 선언
int sorted[MAX_SIZE];

//평균 횟수를 구할 변수선언
int count = 0;
//평균 횟수를 구하기 위한 이동 및 비교 횟수를 넣을 리스트 선언
int m_compar[20], m_move[20];
//이동 및 비교 횟수를 위한 전역 변수 선언
int compare = 0;
int move = 0;

//리스트 초기화 함수
void init_list(int arr[]) {
	for (int i = 0; i < 20; i++) {
		arr[i] = 0;
	}
}

// 랜덤으로 난수 20개를 만드는 함수
void RandomArray(int arr[]) {
	for (int i = 0; i < 20; i++) {
		arr[i] = rand() % 100; //0부터 99까지의 난수를 생성한 후 리스트에 저장
	}
}

// 비교 횟수와 이동 횟수 평균 구하는 함수
void result(int move[], int compar[]) {
	int m_result = 0;
	int c_result = 0;

	for (int i = 0; i < 20; i++) {
		m_result += move[i];
		c_result += compar[i];
	}

	printf("평균 이동 횟수 : %d\n", (m_result / 20));
	printf("평균 비교 횟수 : %d\n", (c_result / 20));
}

// 배열 출력 함수
void printArray(int arr[]) {
	for (int i = 0; i < 20; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

//리스트를 정렬 후 합병 하는 함수
void merge(int arr[], int left, int mid, int right, int count) {
	int i, j, k, l; //반복문에 사용할 변수를 선언
	//비교 및 이동 횟수 변수 선언
	i = left;
	j = mid + 1;
	k = left;

	// 분할 정렬된 list의 합병
	while (i <= mid && j <= right) {
		compare++; // 비교 횟수 증가
		if (arr[i] <= arr[j])
			sorted[k++] = arr[i++];
		else
			sorted[k++] = arr[j++];
		move++; // 이동 횟수 증가
	}

	// 남아 있는 레코드의 일괄 복사
	if (i > mid) {
		for (l = j; l <= right; l++) {
			sorted[k++] = arr[l];
			move++; // 이동 횟수 증가
		}
	}
	else {
		for (l = i; l <= mid; l++) {
			sorted[k++] = arr[l];
			move++; // 이동 횟수 증가
		}
	}

	// 배열 sorted[]의 리스트를 배열 list[]로 복사
	for (l = left; l <= right; l++)
		arr[l] = sorted[l];

	if (count == 0) {
		for (int i = 0; i < MAX_SIZE; i++)
			printf("%d ", arr[i]);
		printf("\n");
	}
}

//합병 정렬 함수
void merge_sort(int arr[], int left, int right, int count) {
	int mid;

	if (count == 0)
		printf("Merge Sort\n");

	//리스트를 균등 분활하여 값을 비교하는 반복문을 선언
	for (int size = 1; size <= right - left; size = 2 * size) {
		//균등 분활한 부분에서 왼쪽 비교하는 반복문
		for (int start = left; start <= right - size; start += 2 * size) {
			mid = start + size - 1;
			int end = start + 2 * size - 1;
			if (end > right)
				end = right;
			merge(arr, start, mid, end, count);
		}
	}

	if (count == 0) {
		printf("Average Move Count : %d\n", move);
		printf("Average Compare Count : %d\n", compare);
	}

	//평균 리스트에 이동 및 비교 횟수 저장
	m_compar[count] = compare;
	m_move[count] = move;
}


int main() {

	int m_list[20];

	RandomArray(m_list);
	printf("Original LIst\n");
	printArray(m_list);
	printf("\n");
	merge_sort(m_list, 0, MAX_SIZE - 1, count);

    count++;

    for (int i = 1; i < 20; i++) {
		//이동 및 비교 횟수 초기화
		compare = 0;
		move = 0;
        //선택 정렬
        init_list(m_list);
        RandomArray(m_list); // 랜덤 리스트 생성
        merge_sort(m_list, 0, MAX_SIZE-1 ,count); //합병 정렬 실행

        count++;
    }

	printf("\n<합병 정렬의 평균 횟수 출력>\n");
	result(m_move, m_compar);

	return 0;
}