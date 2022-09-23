#include <node.h>
#include <uv.h>
#include <iostream>

using namespace std;

template <class T>
class IGenericTypeFn {
    public:
        virtual T m(T num)=0;
};

template <class T>
class GenericTypeFn: public IGenericTypeFn<T> {
    public:
        GenericTypeFn() {

        }
        
        T m(T num) {
            return num;
        }
};

template <typename T, typename U>
T getNum(U theCls, T num) {
    return theCls->m(num);
};

template <typename T, typename U>
int printNum(U ob, T num) {
    cout << getNum(ob, num) << endl;
    return 0;
};


namespace multiIsolateTest {
    using v8::FunctionCallbackInfo;
    using v8::Local;
    using v8::Value;
    using v8::String;
    using v8::Number;
    using v8::Isolate;
    using v8::Context;
    using v8::Object;


    /**
     * @brief ss
     * 
     * @param args 
     */
    void Method(const FunctionCallbackInfo<Value>&args) {

        Isolate* isolate = args.GetIsolate();

        GenericTypeFn<int>* A = new GenericTypeFn<int>();
        GenericTypeFn<double>* B = new GenericTypeFn<double>();
        int ss = printNum(A, 12);
        int s = printNum(B, 12.3);

        args.GetReturnValue().SetNull();
    }

    void Initialize(Local<Object> exports) {
        NODE_SET_METHOD(exports, "cppTemplateTest", Method);
    }

    NODE_MODULE(NODE_MODULE_NAME, Initialize);
}