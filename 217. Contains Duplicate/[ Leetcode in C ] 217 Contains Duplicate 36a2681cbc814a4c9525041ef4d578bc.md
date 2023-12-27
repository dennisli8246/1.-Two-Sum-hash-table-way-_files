# [ Leetcode in C ] 217. Contains Duplicate

![Untitled](%5B%20Leetcode%20in%20C%20%5D%20217%20Contains%20Duplicate%2036a2681cbc814a4c9525041ef4d578bc/Untitled.png)

# question : **[217. Contains Duplicate](https://leetcode.com/problems/contains-duplicate/)**

Given an integer array `nums`, return `true` if any value appears **at least twice** in the array, and return `false` if every element is distinct.

在一整數數列中找出是否有重複的數字，如果有return true

****Example 1:****

```c
Input: nums = [1,2,3,1] Output: true
```

****Example 2:****

```c
Input: nums = [1,2,3,4] Output: false
```

****Example 3:****

```c
Input: nums = [1,1,1,3,3,4,3,2,4,2] Output: true
```

****Constraints:****

```c
1 <= nums.length <= 105
-109 <= nums[i] <= 109
```

## 使用**UT_hash_handle hh**

先宣告資料結構，並且可以被UT_hash_handle hh使用與找尋。

```c
struct node{
    int val;
    UT_hash_handle hh;
};
```

宣告table

```c
struct node *table =NULL;
```

自訂函數是可以在hash table中增加資料的函式add()

```c
void add(int val){
    struct node *s;
    s=malloc(sizeof(struct node));
    s->val = val;
    HASH_ADD_INT(table,val,s);
}
```

主迴圈

```c
bool containsDuplicate(int* nums, int numsSize){
    table =NULL;//將table 初始化NULL
    for(int i=0;i<numsSize;i++){
        struct node*check;
        HASH_FIND_INT(table,&nums[i],check);//在table中尋找有沒有這個數字被記錄過
        if(check==NULL){
            add(nums[i]);
        }else{//如果找不到就用add()增加
            return true;
        }
    }
    return false;//最後如果都找不到就return false
}
```

## 使用**sorting**

假設一個array如下

**Num=[-20 -2 -20 5 3 4]**

經過sort排列過後

**Num=[-2 -20 -20 3 4 5]**

當迴圈一次判斷num[i]是否等於num[i+1]

範例當i=1時Num[i]=20會等於Num[i+1]所以就可以判斷出是否有重複

qsort比較函數

```c
int comp(const void*a, const void*b){
    return(*(int*)a - *(int*)b);
}
```

主迴圈

```c
bool containsDuplicate(int* nums, int numsSize){
 
    qsort(nums,numsSize,sizeof(int),comp);
    //printf("\n");
    for(int i=0 ; i< numsSize-1 ; i++){
        //printf("%d ",nums[i]);
        if(nums[i]==nums[i+1]){return true;}
    }
 
    return false;
}
```

## 總結

如果使用qsort的方式來解，會比較占用時間，因為sorting的過程其實還是會跑回圈

![Untitled](%5B%20Leetcode%20in%20C%20%5D%20217%20Contains%20Duplicate%2036a2681cbc814a4c9525041ef4d578bc/Untitled%201.png)

如果使用hash table的方式來解會比較占用空間資源

![Untitled](%5B%20Leetcode%20in%20C%20%5D%20217%20Contains%20Duplicate%2036a2681cbc814a4c9525041ef4d578bc/Untitled%202.png)