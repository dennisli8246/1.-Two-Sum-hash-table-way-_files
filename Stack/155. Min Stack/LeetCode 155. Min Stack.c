
// Online C Compiler - Build, Compile and Run your C programs online in your favorite browser
#include<stdlib.h>
#include<stdio.h>
#define LEN 0xffff


typedef struct {
    int *data;
    int top;
} MinStack;


MinStack* minStackCreate() {
    MinStack *obj=malloc(sizeof(MinStack));
    obj->data = malloc(sizeof(int)*LEN);
    obj->top = -1;
    return obj;
}

void minStackPush(MinStack* obj, int val) {

    obj->top++;
    obj->data[obj->top] = val;
    //printf("top=%d -> Push=%d ",obj->top,obj->data[obj->top]);
}

void minStackPop(MinStack* obj) {
  obj->top--;
}

int minStackTop(MinStack* obj) {
  return obj->data[obj->top];
}

int minStackGetMin(MinStack* obj) {
    int min= obj -> data[0];
    //printf("top=%d ",obj->top);
    for(int i=0; i <= obj->top ;i++){
        printf("i=%d=>%d ",i,obj->data[i]);
        if( obj->data[i] < min){
            min=obj->data[i];
        }
    }
  return min;
}

void minStackFree(MinStack* obj) {
    free(obj);
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * MinStack* obj = minStackCreate();
 * minStackPush(obj, val);
 
 * minStackPop(obj);
 
 * int param_3 = minStackTop(obj);
 
 * int param_4 = minStackGetMin(obj);
 
 * minStackFree(obj);
*/
int main()
{   
    MinStack* obj = minStackCreate();
    minStackPush(obj, -2);
    minStackPush(obj, 0);
    minStackPush(obj, -3);
    printf("%d\n",minStackGetMin(obj));
    minStackPop(obj);
    printf("%d\n",minStackTop(obj));
    printf("%d\n",minStackGetMin(obj));
    printf("Welcome to Online IDE!! Happy Coding :)");
    return 0;
}
