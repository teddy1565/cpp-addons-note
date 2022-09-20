#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <node.h>
#include <iostream>

typedef struct{
    char res[600];
}_String;

typedef struct{
    struct power{
        int n,m;
    }power;
    char a[600],b[600],c[600],d[600];
}Karatsuba_str_format;

typedef struct{
    struct power_str{
        char a[600],b[600],c[600],d[600];
    }power;
    char a[600],b[600],c[600],d[600];
    _String temp;
}Karatsuba_result_str;

static int Div_expansion_match(char *s1,char *s2){
    int state=0;
    int i,leng = strlen(s1);
    int n=0;
    if(strlen(s2)>strlen(s1)){
        state = 1;
    }else if(strlen(s1)==strlen(s2)){
        state = 2;
        for(i=0;i<leng;i++){
            n = (s1[i]-'0')-(s2[i]-'0');
            if(n>0){
                state = 0;
                break;
            }else if(n<0){
                state = 1;
                break;
            }
        }
    }
    return state;
}

void split(char *str,char *left,char *operator_,char *right){
    while(*str!=' '){
        *left++ = *str++;
    }
    *left='\0';
    *str='\0';
    while(*++str!=' '){
        *operator_ = *str;
    }
    while(*++str!='\0'){
        if(*str=='\n')break;
        *right++ = *str;
    }
    *right = '\0';
}

static _String Add_expansion_process(char *res){
    int i,m;
    char *response;
    _String sresponse;
    for(i=0;i<=strlen(res);i++){
        if(i==strlen(res)){
            response = (char*)malloc(sizeof(char)*(2));
            response[0]='0';
            response[1]='\0';
            break;
        }else if(res[i]!='0'){
            response = (char*)malloc(sizeof(char)*(strlen(res)-i+1));
            memmove(response,&res[i],strlen(res));
            response[strlen(res)-i]='\0';
            break;
        }
    }
    free(res);
    strcpy(sresponse.res,response);
    free(response);
    return sresponse;
}

static int Zero_check(char *s1,char *s2){
    int i,f;
    for(i=0;i<=strlen(s1);i++)if(s1[i]!='0')break;
    f = i==strlen(s1)?1:0;
    for(i=0;i<=strlen(s2);i++)if(s2[i]!='0')break;
    f = i==strlen(s2)?2:0;
    return f;
}

static _String Add(char *str1,char *str2){
    char *result = (char*)malloc(sizeof(char)*(strlen(str1)+2));
    int i,j,m,tmp,num;
    result[strlen(str1)+1]='\0';
    for(i=strlen(str1),j=strlen(str1)-1,m=strlen(str2)-1,tmp=0;i>=0;i--,j--,m--){
        num = (j>=0?str1[j]-'0':0)+(m>=0?str2[m]-'0':0)+tmp;
        tmp=0;
        result[i] = (num%10)+'0';
        tmp = num/10;
    }
    return Add_expansion_process(result);
}

static _String Sub(char *str1,char *str2){
    char *rev = (char*)malloc(sizeof(char)*(strlen(str1)+1));
    _String str;
    int i,j,m,tmp,num;
    rev[strlen(str1)]='\0';
    for(i=strlen(str1)-1,j=10,m=strlen(str2)-1;i>=0;i--,m--){
        rev[i] = (j-(m>=0?str2[m]-'0':0))%10+'0';
        if(str2[m]!='0')j=9;
    }
    strcpy(str.res,rev);
    free(rev);rev=NULL;
    str = Add(str1,str.res);
    rev = (char*)malloc(sizeof(char)*(strlen(str.res)));
    for(i=1;i<strlen(str.res);i++)if(str.res[i]!='0')break;
    for(j=0;i<strlen(str.res);i++,j++)rev[j] = str.res[i];
    if(j!=0)rev[j] = '\0';
    else{
        rev[0]='0';
        rev[1]='\0';
    }
    strcpy(str.res,rev);
    free(rev);rev=NULL;
    if(Zero_check(str1,str2)==1)str = Add(str2,"0");
    else if(Zero_check(str1,str2)==2)str = Add(str1,"0");
    return str;
}

static _String Mul_expansion_itoa(int n){
    _String response;
    int i,len,r=n;
    for(len=0;n!=0;len++)n/=10;
    response.res[len+1]='\0';
    for(;len>=0;len--){
        response.res[len] = (r%10)+'0';
        r/=10;
    }
    return response;
}

static Karatsuba_str_format Mul_expansion_process(char *str1,char *str2){
    Karatsuba_str_format res;
    int i,m,str_parse_length;
    str_parse_length = (strlen(str1)&1)?(strlen(str1)/2)+1:strlen(str1)/2;
    res.power.n = strlen(str1)/2;
    for(i=0;i<str_parse_length;i++){
        res.a[i] = str1[i];
    }
    res.a[i]='\0';
    str_parse_length = strlen(str1)/2;
    for(m=0;i<strlen(str1);i++,m++){
        res.b[m] = str1[i];
    }
    res.b[m]='\0';
    str_parse_length = (strlen(str2)&1)?(strlen(str2)/2)+1:strlen(str2)/2;
    res.power.m = strlen(str2)/2;
    for(i=0;i<str_parse_length;i++){
        res.c[i] = str2[i];
    }
    res.c[i]='\0';
    str_parse_length = strlen(str2)/2;
    for(m=0;i<strlen(str2);i++,m++){
        res.d[m] = str2[i];
    }
    res.d[m]='\0';
    return res;
}

static _String Mul(char *str1,char *str2){
    _String response;
    Karatsuba_str_format str;
    Karatsuba_result_str result;
    int i,num;
    str = Mul_expansion_process(str1,str2);
    strcpy(response.res,str1);
    if(strlen(str.a)+strlen(str.c)>8){
        result.temp=Mul(str.a,str.c);
        for(i=0;i<str.power.n+str.power.m;i++){
            result.power.a[i]='0';
        }
        result.power.a[i]='\0';
        strcpy(result.a,result.temp.res);
        strcat(result.a,result.power.a);
    }else if(strlen(str.a)+strlen(str.c)<=8){
        result.temp = Mul_expansion_itoa(atoi(str.a)*atoi(str.c));
        for(i=0;i<str.power.n+str.power.m;i++){
            result.power.a[i]='0';
        }
        result.power.a[i]='\0';
        strcpy(result.a,result.temp.res);
        strcat(result.a,result.power.a);
    }
    if(strlen(str.a)+strlen(str.d)>8){
        result.temp=Mul(str.a,str.d);
        for(i=0;i<str.power.n;i++){
            result.power.b[i]='0';
        }
        result.power.b[i]='\0';
        strcpy(result.b,result.temp.res);
        strcat(result.b,result.power.b);
    }else if(strlen(str.a)+strlen(str.d)<=8){
        result.temp=Mul_expansion_itoa(atoi(str.a)*atoi(str.d));
        for(i=0;i<str.power.n;i++){
            result.power.b[i]='0';
        }
        result.power.b[i]='\0';
        strcpy(result.b,result.temp.res);
        strcat(result.b,result.power.b);
    }
    if(strlen(str.c)+strlen(str.b)>8){
        result.temp=Mul(str.c,str.b);
        for(i=0;i<str.power.m;i++){
            result.power.c[i]='0';
        }
        result.power.c[i]='\0';
        strcpy(result.c,result.temp.res);
        strcat(result.c,result.power.c);
    }else if(strlen(str.c)+strlen(str.b)<=8){
        result.temp = Mul_expansion_itoa(atoi(str.c)*atoi(str.b));
        for(i=0;i<str.power.m;i++){
            result.power.c[i]='0';
        }
        result.power.c[i]='\0';
        strcpy(result.c,result.temp.res);
        strcat(result.c,result.power.c);
    }
    if(strlen(str.b)+strlen(str.d)>8){
        result.temp=Mul(str.b,str.d);
        strcpy(result.d,result.temp.res);
    }else if(strlen(str.b)+strlen(str.d)<=8){
        result.temp = Mul_expansion_itoa(atoi(str.b)*atoi(str.d));
        strcpy(result.d,result.temp.res);
    }
    if(strlen(str1)+strlen(str2)>8){
        response = Add(result.a,result.b);
        response = Add(response.res,result.c);
        response = Add(response.res,result.d);
    }else if(strlen(str1)+strlen(str2)<=8){
        num = atoi(str1)*atoi(str2);
        for(i=9;i>=0;i--){
            result.temp.res[i]=((num>0?num%10:0)+'0');
            num/=10;
        }
        result.temp.res[10]='\0';
        for(i=0;i<=10;i++){
            if(i==10){
                response.res[0]='0';
                response.res[1]='\0';
            }
            if(result.temp.res[i]!='0')break;
        }
        if(i!=10){
            for(num=0;i<=10;i++,num++){
                response.res[num] = result.temp.res[i];
            }
        }
    }
    return response;
}

static _String Div(char *str1,char *str2){
    _String response = Add("0","0");
    _String Division_n = Add("0","1");
    _String MOD_num = Add("0","0");
    _String Split_str,tmp;
    char catcher[2];
    int i,m=0,str1L=strlen(str1);
    catcher[1]='\0';
    if(Zero_check(str1,str2)==0){
        for(i=0;i<strlen(str2);i++,m++){
            Split_str.res[i] = str1[m];
        }
        Split_str.res[i]='\0';
        tmp = Mul(str2,Division_n.res);
        while(Div_expansion_match(Split_str.res,tmp.res)!=1){
            Division_n = Add(Division_n.res,"1");
            tmp = Mul(str2,Division_n.res);
        }
        Division_n = Sub(Division_n.res,"1");
        tmp = Mul(str2,Division_n.res);
        MOD_num = Sub(Split_str.res,tmp.res);
        response = Add(response.res,Division_n.res);
        for(;m<str1L;m++){
            Division_n = Add("1","0");
            catcher[0]=str1[m];
            strcat(MOD_num.res,catcher);
            strcpy(Split_str.res,MOD_num.res);
            Split_str = Add(Split_str.res,"0");
            tmp = Mul(str2,Division_n.res);
            while(Div_expansion_match(Split_str.res,tmp.res)!=1){
                Division_n = Add(Division_n.res,"1");
                tmp = Mul(str2,Division_n.res);
            }
            Division_n = Sub(Division_n.res,"1");
            tmp = Mul(str2,Division_n.res);
            if(Div_expansion_match(Split_str.res,tmp.res)==0)MOD_num = Sub(Split_str.res,tmp.res);
            else if(Div_expansion_match(Split_str.res,tmp.res)!=0)MOD_num = Add("0","0");
            response = Mul(response.res,"10");
            response = Add(response.res,Division_n.res);
        }
    }else{
        response = Add("0","0");
    }
    return response;
}

namespace arithmetic {
    using namespace std;
    using v8::FunctionCallbackInfo;
    using v8::Isolate;
    using v8::Local;
    using v8::Object;
    using v8::Number;
    using v8::Value;
    using v8::String;
    using v8::Context;
    
    char keyin[600],left[600],right[600],operator_;
    
    void Method(const FunctionCallbackInfo<Value>&args) {
        
        Isolate* isolate = args.GetIsolate();
        Local<String> inputString = Local<String>::Cast(args[0]);
        String::Utf8Value v8_inputString(isolate, Local<String>::Cast(args[0]));
        // string s = string(*v8_inputString);
        split(*v8_inputString, left, &operator_, right);
        // printf("%s", *v8_inputString);
        _String r;
        int a = Div_expansion_match(left,right);
        if(operator_=='+')r = Add(left,right);
        else if(operator_=='-')r = a==0?Sub(left,right):Sub(right,left);
        else if(operator_=='*')r = Mul(left,right);
        else if(operator_=='/')r = Div(left,right);

        auto payload = String::NewFromUtf8(isolate, r.res).ToLocalChecked();

        if(a==1&&operator_=='-') {
            auto f = String::NewFromUtf8(isolate, "-").ToLocalChecked();
            auto result = String::Concat(isolate, f, payload);
            args.GetReturnValue().Set(result);
        } else {
            args.GetReturnValue().Set(payload);
        }
    }

    void Initialize(Local<Object> exports) {
        NODE_SET_METHOD(exports, "arithmetic", Method);
    }

    NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize);
}

// int main(){
//     char keyin[600],left[600],right[600],operator_;
//     int a=0;
//     String r;
//     while(fgets(keyin,600,stdin)!=NULL){
//         split(keyin,left,&operator_,right);
        // a = Div_expansion_match(left,right);
        // if(operator_=='+')r = Add(left,right);
        // else if(operator_=='-')r = a==0?Sub(left,right):Sub(right,left);
        // else if(operator_=='*')r = Mul(left,right);
        // else if(operator_=='/')r = Div(left,right);
        // if(a==1&&operator_=='-')printf("-%s\n",r.res);
        // else printf("%s\n",r.res);
//     }
//     return 0;
// }