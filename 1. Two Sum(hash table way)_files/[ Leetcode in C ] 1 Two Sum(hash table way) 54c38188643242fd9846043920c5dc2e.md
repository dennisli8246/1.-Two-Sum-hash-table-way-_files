# [ Leetcode in C ] 1. Two Sum(hash table way)

# question : **[1. Two Sum](https://leetcode.com/problems/two-sum/)**

題目會任意出一個矩陣包含整數例如[2,7,11,15]，並且給予一個target，假設為9。程式需要找到哪兩個數字可以組成為9。如下範例，因為可以第0與1的數值為2與7加起來就可以等於9。所以我們只要輸出為[0,1]即可。

**Example 1:**

```
Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
```

# 簡單的方法就是用兩層迴圈

第一層迴圈由矩陣的第[0]開始尋找，直到第n個。第二個迴圈由i+1開始找。如果有找到就結束迴圈。但是這方非常耗時間，因為要使用O(n^2)的時間複雜度。所以等等會介紹hash table，此用空間來換取時間。如下表，target為4，矩陣為[2,1,5,3]當跑第一次迴圈的時候找到2+1,2+5,2+3。當跑第二次迴圈的時候比對1+5,1+3。其中1+3=4就是我們的target也就是答案了。但有沒有想過當第一次跑的時候比對到2+3我們其實已經找到3這個數字了，所以如果有一張表可以記錄這些可能的數字，這樣只需要一次就可以照到答案了。

![Untitled](%5B%20Leetcode%20in%20C%20%5D%201%20Two%20Sum(hash%20table%20way)%2054c38188643242fd9846043920c5dc2e/Untitled.png)

```c

int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    int *ans = malloc( sizeof(int) * 2 );
    for(int i=0; i<numsSize ;i++ ){
        for(int j=i+1 ; j<numsSize ; j++ ){
            if( ( nums[i] + nums[j] ) == target){
                ans[0]=i;
                ans[1]=j;
            }
        }
    }
    * returnSize =2;
    return ans;
}
```

# 以下會使用hash table來做比較優的解法

1. 建立資料結構，並且在結構中宣告UT_hash_handle hh，之後我要使用hash table就可以直接使用，並且就是用這個結構放在table

```c
struct node{
    int val;
    int index;
    UT_hash_handle hh;
};
```

1. 宣告剛剛建立的結構這就是一個hash table

```c
struct node *table = NULL;
```

1. 建立一個子function可以在table上面新增node的資料結構

```c
void add_val(int val, int index){
    struct node *s;
    s=malloc(sizeof(struct node));
    s->val = val;
    s->index = index;
    HASH_ADD_INT(table,val,s);
}

其中
HASH_ADD_INT(table,val,s) 
就是(所要放入的table,val數值,index)
```

1. 主程式
    1. table = NULL//記得要初始化，不然前一題的table會殘留到下一題
    2. malloc ()是因為要跟記憶體先要兩個int的空間
    3. 只需要建立一個迴圈
    4. 宣告一個名為check的node(之前所做的資料結構包含val 和 index )
    
    ```c
    struct node *check;
    
    ```
    
    e. 用UT_hash_handle hh;所做的函式來找到有之前處存過的資料，其中&rem為記錄與target的差異值。比較看看我們的table中有沒有這個數值
    
    ```c
    HASH_FIND_INT( table, &rem, check );
    ```
    
    f. HASH_FIND_INT 如果沒有有找到就會return NULL， 如果沒有這個數值就將這組數據存到table中(使用HASH_ADD_INT(table,val,check);)，如果有找到就出答案。
    
    ```c
                ans[0]=check->index;
                ans[1]=i;
    ```
    

```c
int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    table = NULL; //記得要初始化，不然前一題的table會殘留到下一題
    int *ans = malloc( sizeof(int) * 2 );
    int rem;
    * returnSize =2;// 固定有兩個值

    for(int i = 0 ; i<numsSize; i++){
        rem = ( target - nums[i] ) ;
        struct node *check;
        HASH_FIND_INT( table, &rem, check );
        //check num2Table if table have needed val
        if( check != NULL  ){
            ans[0]=check->index;
            ans[1]=i;
        }else{
            check=malloc(sizeof(struct node));
            check->val =  nums[i] ;
            check->index = i;
            HASH_ADD_INT(table,val,check);
        }

    }
```

1. 圖解使用hash table的圖示
    1. 當i=0的時候計算 rem = ( target - nums[i] )(也就是跟target 差多少就是我們要的答案)，並且記錄nums[i]在table中val=2
        
        ![Untitled](%5B%20Leetcode%20in%20C%20%5D%201%20Two%20Sum(hash%20table%20way)%2054c38188643242fd9846043920c5dc2e/Untitled%201.png)
        
    2. 當i=1，確認表中沒有val=3會等於我的rem ，沒有就記錄我的nums[i]在table中val=1
        
        ![Untitled](%5B%20Leetcode%20in%20C%20%5D%201%20Two%20Sum(hash%20table%20way)%2054c38188643242fd9846043920c5dc2e/Untitled%202.png)
        
    3. 當i=2，確認表中沒有val=-1會等於我的rem ，沒有就記錄我的rem在table中val=5
        
        ![Untitled](%5B%20Leetcode%20in%20C%20%5D%201%20Two%20Sum(hash%20table%20way)%2054c38188643242fd9846043920c5dc2e/Untitled%203.png)
        
    4. 當i=3，確認表中沒有val=1會等於我的rem=4-3 
        
        
        ![Untitled](%5B%20Leetcode%20in%20C%20%5D%201%20Two%20Sum(hash%20table%20way)%2054c38188643242fd9846043920c5dc2e/Untitled%204.png)
        
    5. 其中table中由當i=1紀錄的nums[1]=val=3與rem相同，也就是答案了
        
        
        ![Untitled](%5B%20Leetcode%20in%20C%20%5D%201%20Two%20Sum(hash%20table%20way)%2054c38188643242fd9846043920c5dc2e/Untitled%205.png)
        
        # 總結
        
        hash table 的運用可以讓空間換取迴圈的時間，UT_hash_handle hh是C語言的一種結構，當然我們也可以自己創建自己的hash table來使用。但可能會需要注意一些規則。總之hash table就是一個將很大範圍的陣列縮減在一張小table以便可以方便尋找資料的方法。