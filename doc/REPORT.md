# HW2 Polynomial

## 1.解題說明

a.定義多項式類別及其數據成員。

b.設計多項式的基本操作，例如加法、減法、乘法等。

c.重載 << 和 >> 操作符，用於輸入和輸出多項式。

d.進行測試驗證函數的正確性。

### 舉例說明
一個多項式可以表示為 $3x^2+2x+1$ ，我們需要先設計一個類別來儲存這些係數和指數，再進行加法與乘法的運算。

## 2.演算法設計與實作

### 加法運算

```cpp
Polynomial Polynomial::Add(Polynomial& other){
    Polynomial result; //儲存結果
    int aPos=0,bPos=0; //用來計算目前位置
    while(aPos<terms&&bPos<other.terms){
        if(termArray[aPos].exp==other.termArray[bPos].exp){
            float sum=termArray[aPos].coef+other.termArray[bPos].coef;
            if(sum) result.newTerm(sum,termArray[aPos].exp);
            aPos++;
            bPos++;
        } //指數相等，係數相加，aPos與bPos各加1指向下一個位置
        else if(termArray[aPos].exp>other.termArray[bPos].exp){
            result.newTerm(termArray[aPos].coef,termArray[aPos].exp);
            aPos++;
        } //如果aPos所指位置的指數比較大，將此位置的指數與係數放入result,aPos加1
        else{
            result.newTerm(other.termArray[bPos].coef,other.termArray[bPos].exp);
            bPos++;
        } //反之
    }
    for(;aPos<terms;aPos++){
        result.newTerm(termArray[aPos].coef,termArray[aPos].exp);
    }
    for(;bPos<terms;bPos++){
        result.newTerm(other.termArray[bPos].coef,other.termArray[bPos].exp);
    } //如果有剩餘項，直接放入result
    return result;
}
```

### 乘法運算

```cpp
Polynomial Polynomial::Mult(Polynomial& other){
    Polynomial result; //最終結果
    Polynomial temp; //儲存未整理的乘法多項式
    for(int i=0;i<terms;i++){
        for(int j=0;j<other.terms;j++){
            temp.newTerm(termArray[i].coef*other.termArray[j].coef,termArray[i].exp+other.termArray[j].exp);
        }
    } //計算多項式每一項之間的乘積
    for(int i=0;i<temp.terms;i++){
        bool found=false;
        for(int j=0;j<result.terms;j++){
            if (result.termArray[j].exp == temp.termArray[i].exp) {
                result.termArray[j].coef += temp.termArray[i].coef;
                found = true;
                break;
            }
        }
        if(!found){
            result.newTerm(temp.termArray[i].coef,temp.termArray[i].exp);
        }
    } //將有相同指數的係數相加放入result
    return result;
}
```

## 3.效能分析

### 時間複雜度

a.  Add:O( $m+n$ ) 其中 n 為第一個多項式的項數，m 為第二個多項式的項數

b.  Mult:O( $n^2 \times m^2$ )

c.  Eval:O(n)

### 空間複雜度

a.  Add:O( $m+n$ )

b.  Mult:O( $n \times m$ )

c.  Eval:O(1)

## 4.測試

```
Enter polynomial p1:
Enter the number of terms: 3
Enter coefficient and exponent: 3 2
Enter coefficient and exponent: 2 1
Enter coefficient and exponent: 1 0
Enter polynomial p2:
Enter the number of terms: 3
Enter coefficient and exponent: 3 2
Enter coefficient and exponent: 2 1
Enter coefficient and exponent: 1 0
Polynomial p1: 3x^2 + 2x^1 + 1x^0
Polynomial p2: 3x^2 + 2x^1 + 1x^0
Polynomial p1 + p2: 6x^2 + 4x^1 + 2x^0
Polynomial p1 * p2: 9x^4 + 12x^3 + 10x^2 + 4x^1 + 1x^0
Enter a value to evaluate p1: 5 
p1(5) = 86
```

## 5.心得討論

通過這次作業，我學習到如何用電腦邏輯去實現多項式的加法與乘法，理解到對於我們而言簡單幾步驟就能計算出來的，如果希望通過電腦來表示，需要好幾次的比較才能計算出結果。
