typedef struct ArrayList {
    int memberNum;
    int space;
    void ** arr;
} ArrayList;

ArrayList *new_array_list() {
    ArrayList *arrayList = (ArrayList *)malloc(sizeof(ArrayList));
    arrayList->memberNum = 0;
    arrayList->space = 5;
    arrayList->arr = (void **)malloc(sizeof(void *) * arrayList->space);
    return arrayList;
}

void append_new_node(ArrayList *arrayList, void *item) {
    if (arrayList->memberNum == arrayList->space) {
        arrayList->space = arrayList->space * 2;
        void ** arr = (void **)malloc(sizeof(void *) * arrayList->space);
        int i;
        for (i = 0; i < arrayList->memberNum; i++) {
            arr[i] = arrayList->arr[i];
        }
        free(arrayList->arr);
        arrayList->arr = arr;
    }
    arrayList->arr[arrayList->memberNum++] = item;
}

// int main() {
//     ArrayList *arrList = new_array_list();
//     int one = 32131;
//     int two = 231;
//     int *ione = &one;
//     int *itwo = &two;
//     append_new_node(arrList, ione);
//     append_new_node(arrList, itwo);
//     append_new_node(arrList, itwo);
//     append_new_node(arrList, itwo);
//     append_new_node(arrList, itwo);
//     append_new_node(arrList, itwo);
//     append_new_node(arrList, itwo);
//     append_new_node(arrList, itwo);
//     int *get = (int *)arrList->arr[0];
//     int *get_ = (int *)arrList->arr[6];
//     printf("RESULT %d\n", *get);
//     printf("RESULT %d\n", *get_);
//     puts("END");
//     return 0;
// }