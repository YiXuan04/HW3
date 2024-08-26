# HW2 Polynomial(circular linked list)

## 1.解題說明

a.定義多項式類別及其數據成員。

b.設計多項式的基本操作，例如加法、減法、乘法等。

c.重載 << 和 >> 操作符，用於輸入和輸出多項式。

d.進行測試驗證函數的正確性。

### 舉例說明
一個多項式可以表示為 $3x^2+2x+1$ ，我們需要先設計一個類別來儲存這些係數和指數，再進行加法與乘法的運算。

## 2.演算法設計與實作

### 類別class&結構class宣告

```cpp
struct Node{
    int coef,exp;
    Node* link;
    Node(int c,int e):coef(c),exp(e),link(nullptr){}
};
class Polynomial{
    private:
        Node* head;
    public:
        Polynomial();
        friend istream& operator>>(istream& is,Polynomial& x);
        friend ostream& operator<<(ostream& os,Polynomial& x);
        Polynomial(const Polynomial& a);
        const Polynomial& operator=(const Polynomial& a);
        ~Polynomial();
        Polynomial operator+(const Polynomial& b);
        Polynomial operator-(const Polynomial& b);
        Polynomial operator*(const Polynomial& b);
        float Eval(float x);
};
```

### 加法運算

```cpp
Polynomial Polynomial::operator+(const Polynomial& b){
    Polynomial result;
    Node* aPtr=head->link;
    Node* bPtr=b.head->link;
    Node* last=result.head;
    while(aPtr!=head&&bPtr!=b.head){
        if(aPtr->exp==bPtr->exp){
            int sumC=aPtr->coef+bPtr->coef;
            if(sumC!=0){
                Node* newNode=new Node(sumC,aPtr->exp);
                last->link=newNode;
                last=newNode;
            }
            aPtr=aPtr->link;
            bPtr=bPtr->link;
        }
        else if(aPtr->exp>bPtr->exp){
            Node* newNode=new Node(aPtr->coef,aPtr->exp);
            last->link=newNode;
            last=newNode;
            aPtr=aPtr->link;
        }
        else{
            Node* newNode=new Node(bPtr->coef,bPtr->exp);
            last->link=newNode;
            last=newNode;
            bPtr=bPtr->link;
        }
    }
    while(aPtr!=head){
        Node* newNode=new Node(aPtr->coef,aPtr->exp);
        last->link=newNode;
        last=newNode;
        aPtr=aPtr->link;
    }
    while(bPtr!=b.head){
        Node* newNode=new Node(bPtr->coef,bPtr->exp);
        last->link=newNode;
        bPtr=bPtr->link;
    }
    last->link=result.head;
    return result;
}
```

### 乘法運算

```cpp
Polynomial Polynomial::operator*(const Polynomial& b){
    Polynomial result;
    Node* aPtr = head->link;
    while(aPtr != head){
        Node* bPtr = b.head->link;
        while(bPtr != b.head){
            int newCoef = aPtr->coef * bPtr->coef;
            int newExp = aPtr->exp + bPtr->exp;
            Node* rPtr = result.head;
            while (rPtr->link != result.head && rPtr->link->exp > newExp) {
                rPtr = rPtr->link;
            }
            if (rPtr->link != result.head && rPtr->link->exp == newExp) {
                rPtr->link->coef += newCoef;
                if (rPtr->link->coef == 0) {
                    Node* temp = rPtr->link;
                    rPtr->link = temp->link;
                    delete temp;
                }
            }
            else{
                Node* newNode = new Node(newCoef, newExp);
                newNode->link = rPtr->link;
                rPtr->link = newNode;
            }
            bPtr = bPtr->link;
        }
        aPtr = aPtr->link;
    }
    return result;
}
```

## 3.效能分析

### 時間複雜度

a.  Polynomial():O(1)，僅初始化頭節點

b.  operator>>&operator<<&operator=:O(n)

c.  operator+&operator-:O( $m+n$ ) 其中 n 為第一個多項式的項數，m 為第二個多項式的項數

d.  operator*:O( $n \times m$ )

e.  Eval:O(n)

### 空間複雜度

a.  Polynomial()&operator<<:O(1)

b.  operator>>&operator=:O(n)

c.  operator+&operator-:O( $m+n$ ) 其中 n 為第一個多項式的項數，m 為第二個多項式的項數

d.  operator*:O( $n^2 \times m^2$ )

e.  Eval:O(1)

## 4.測試

```
Enter the first polynomial(only input coef exp): 
Enter the number of terms: 3
Enter coefficient and exponent: 3 2
Enter coefficient and exponent: 2 1
Enter coefficient and exponent: 1 0
Enter the second polynomial(only input coef exp):
Enter the number of terms: 3
Enter coefficient and exponent: 4 2
Enter coefficient and exponent: 3 1
Enter coefficient and exponent: 2 0
Add Result:7x^2 5x^1 3x^0
Subtraction Result:-1x^2 -1x^1 -1x^0
Multiplication Result:12x^4 17x^3 16x^2 7x^1 2x^0
Enter a value:5
P1(5)=86
P2(5)=117
Press any key to continue . . . 
```

## 5.心得討論

將上次作業內容改成以環狀鏈結的方式處理，通過這次作業，我學習到如何用電腦邏輯去實現多項式的加法與乘法，理解到對於我們而言簡單幾步驟就能計算出來的，如果希望通過電腦來表示，需要好幾次的比較才能計算出結果。
