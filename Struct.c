typedef struct StructVariable {
    char *type;
    char *ID;
    int dimension;
    char *structID;
    struct StructAttribute * attribute;
} StructVariable;

StructVariable *new_struct_variable() {
    StructVariable *variable = (StructVariable *)malloc(sizeof(StructVariable));
    variable->type = NULL;
    variable->ID = NULL;
    variable->dimension = 0;
    variable->structID = NULL;
    variable->attribute = NULL;
}

typedef struct StructAttribute {
    struct StructVariable ** varDec;
    int varNum;
} StructAttribute;

StructAttribute *new_struct_attribute(int varNum) {
    StructAttribute *attribute = (StructAttribute *)malloc(sizeof(StructAttribute));
    attribute->varDec = (StructVariable **)malloc(sizeof(StructVariable *) * varNum);
    attribute->varNum = varNum;
    memset(attribute->varDec, 0, sizeof(StructVariable *) * varNum);
    return attribute;
}

typedef struct StructVariableAttribute {
    int dimension;
    StructAttribute *structAttribute;
} StructVariableAttribute;

StructVariableAttribute *new_struct_variable_attribute() {
    StructVariableAttribute *attribute = (StructVariableAttribute *)malloc(sizeof(StructVariableAttribute));
    attribute->dimension = 0;
    attribute->structAttribute = NULL;
    return attribute;
}
/*-----------------------------------------------------*/

// left > right: 1, left < right: 0, left = right: -1
int compare(char *left, char *right) {
    int index = 0;
    while(left[index] && right[index]) {
        if (left[index] > right[index]) {
            return 1;
        } else if (left[index] < right[index]) {
            return 0;
        } else {
            index++;
        }
    }
    if (left[index] == 0) {
        if (right[index] == 0) {
            return -1;
        } else {
            return 0;
        }
    }
    if (right[index] == 0) {
        return 1;
    }
}

void swap(char **left, char **right) {
    char *tmp;
    tmp = *left;
    *left = *right;
    *right = tmp;
}

void swapVariable(StructVariable **left, StructVariable **right) {
    StructVariable *tmp;
    tmp = *left;
    *left = *right;
    *right = tmp;
}

void printf_struct_varDec(StructVariable **varDec, int varNum) {
    int index = 0;
    for (int index = 0; index < varNum; index++) {
        StructVariable *variable = varDec[index];
        printf("Variable %d, type:%s, id: %s\ndimension: %d, structID: %s\n", index, variable->type, variable->ID, variable->dimension, variable->structID);
        if (strcmp(variable->type, "struct") == 0) {
            printf("##############\n");
            StructAttribute *attribute = (StructAttribute *)variable->attribute;
            printf("NUM: %d\n", attribute->varNum);
            printf_struct_varDec(attribute->varDec, attribute->varNum);
            printf("##############\n");
        }
    }
}

void printf_struct_attribute(StructAttribute *attribute) {
    printf("STRUCT, varNum: %d:\n", attribute->varNum);
    printf_struct_varDec(attribute->varDec, attribute->varNum);
}

/* https://www.cnblogs.com/hehehaha/p/6332205.html */
void quickSort(char ** arr, StructVariable ** varDec, int left, int right) {
    int i = left, j = right;
    char *pivot = arr[(left + right) / 2];
    while(i <= j) {
        while(compare(arr[i], pivot) == 0) {
            i++;
        }
        while(compare(arr[j], pivot) == 1) {
            j--;
        }
        if (i <= j) {
            swap(&arr[i], &arr[j]);
            swapVariable(&varDec[i], &varDec[j]);
            i++;
            j--;
        }
    }
    if (left < j) {
        quickSort(arr, varDec, left, j);
    }
    if (right > i) {
        quickSort(arr, varDec, i, right);
    }
}

char* concat(StructVariable *v) {
    char *buff = malloc(sizeof(char) * 1024);
    memset(buff, 0, sizeof(buff));
    strcpy(buff, v->type);
    strcat(buff, v->ID);
    char *dimension = malloc(sizeof(char) * 1024);
    sprintf(dimension, "%d", v->dimension);
    // itoa(v->dimension, dimension, 10);
    strcat(buff, dimension);
    if (v->structID != NULL) {
        strcat(buff, v->structID);
    }
    char *re = buff;
    return re;
}

void sort_struct_attribute_varDec(StructAttribute *attribute) {
    char **arr = (char **)malloc(sizeof(char *) * attribute->varNum);
    int index = 0;
    for (index = 0; index < attribute->varNum; index ++) {
        if (attribute->varDec[index] == NULL)
            return;
        arr[index] = concat(attribute->varDec[index]);
    }
    quickSort(arr, attribute->varDec, 0, attribute->varNum - 1);
    for (index = 0; index < attribute->varNum; index ++) {
        free(arr[index]);
    }
    free(arr);
}

// 0: not equal, 1: equal
int compare_if_equal(StructAttribute *struct1, StructAttribute *struct2) {
    if (struct1->varNum == struct2->varNum) {
        int index = 0;
        for (index = 0; index < struct1->varNum; index++) {
            char *str1 = concat(struct1->varDec[index]);
            char *str2 = concat(struct2->varDec[index]);
            if (strcmp(str1, str2)) {
                return 0;
            }
        }
        return 1;
    } else {
        return 0;
    }
}