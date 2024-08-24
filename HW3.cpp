#include <iostream>
#include <math.h>
using namespace std;

struct Node{
    int coef,exp;
    Node* link;
    Node(int c,int e):coef(c),exp(e),link(nullptr){}
};
class Polynomial;
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
Polynomial::Polynomial(){
    head=new Node(0,-1);
    head->link=head;
}
istream& operator>>(istream& is,Polynomial& x){
    int c,e,num;
    Node* last=x.head;
    cout<<"Enter the number of terms: ";
    is>>num;
    for(int i=0;i<num;i++){
        cout<<"Enter coefficient and exponent: ";
        is>>c>>e;
        Node* newNode=new Node(c,e);
        last->link=newNode;
        last=newNode;
    }
    last->link=x.head;
    return is;
}
ostream& operator<<(ostream& os,Polynomial& x){
    Node* current=x.head->link;
    while(current!=x.head){
        os<<current->coef<<"x^"<<current->exp<<" ";
        current=current->link;
    }
    return os;
}
Polynomial::Polynomial(const Polynomial& a){
    head=new Node(0,-1);
    head->link=head;
    Node* currentA=a.head->link;
    Node* last=head;
    while(currentA!=a.head){
        Node* newNode=new Node(currentA->coef,currentA->exp);
        last->link=newNode;
        last=newNode;
        currentA=currentA->link;
    }
    last->link=head;
}
const Polynomial& Polynomial::operator=(const Polynomial& a){
    if(this!=&a){
        while(head->link!=head){
            Node* temp=head->link;
            head->link=temp->link;
            delete temp;
        }
        Node* currentA=a.head->link;
        Node* last=head;
        while(currentA!=a.head){
            Node* newNode=new Node(currentA->coef,currentA->exp);
            last->link=newNode;
            last=newNode;
            currentA=currentA->link;
        }
        last->link=head;
    }
    return *this;
}
Polynomial::~Polynomial(){
    while(head->link!=head){
        Node* temp=head->link;
        head->link=temp->link;
        delete temp;
    }
    delete head;
}
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
Polynomial Polynomial::operator-(const Polynomial& b){
    Polynomial result;
    Node* aPtr=head->link;
    Node* bPtr=b.head->link;
    Node* last=result.head;
    while(aPtr!=head&&bPtr!=b.head){
        if(aPtr->exp==bPtr->exp){
            int diffC=aPtr->coef-bPtr->coef;
            if(diffC!=0){
                Node* newNode=new Node(diffC,aPtr->exp);
                last->link=newNode;
                last=newNode;
            }
            aPtr=aPtr->link;
            bPtr=bPtr->link;
        }
        else if(aPtr->exp > bPtr->exp){
            Node* newNode = new Node(aPtr->coef, aPtr->exp);
            last->link = newNode;
            last = newNode;
            aPtr = aPtr->link;
        }
        else{
            Node* newNode = new Node(-bPtr->coef, bPtr->exp);
            last->link = newNode;
            last = newNode;
            bPtr = bPtr->link;
        }
    }
    while (bPtr != b.head) {
        Node* newNode = new Node(-bPtr->coef, bPtr->exp);
        last->link = newNode;
        last = newNode;
        bPtr = bPtr->link;
    }
    last->link = result.head;
    return result;
}
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
float Polynomial::Eval(float x){
    float result = 0.0;
    Node* current = head->link;
    while (current != head) {
        result += current->coef * pow(x, current->exp);
        current = current->link;
    }
    return result;
}

int main(){
    Polynomial p1,p2,p3,p4,p5;
    cout<<"Enter the first polynomial(only input coef exp): \n";
    cin>>p1;
    cout<<"Enter the second polynomial(only input coef exp): \n";
    cin>>p2;
    p3=p1+p2;
    p4=p1-p2;
    p5=p1*p2;
    cout<<"Add Result:"<<p3<<endl;
    cout<<"Subtraction Result:"<<p4<<endl;
    cout<<"Multiplication Result:"<<p5<<endl;
    float x;
    cout<<"Enter a value:";
    cin>>x;
    cout<<"P1("<<x<<")="<<p1.Eval(x)<<endl;
    cout<<"P2("<<x<<")="<<p2.Eval(x)<<endl;
    system("pause");
    return 0;
}