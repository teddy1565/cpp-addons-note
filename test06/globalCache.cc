#include <node.h>
#include <uv.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <node_api.h>
// #include <semaphore.h>

using namespace std;


namespace globalCache {
    using v8::FunctionCallbackInfo;
    using v8::Local;
    using v8::Value;
    using v8::String;
    using v8::Number;
    using v8::Isolate;
    using v8::Context;
    using v8::Object;
    using v8::External;

    const int SHM_KEY = 32140895;
    const int SHM_SIZE = 2048;

    char* ToString(const String::Utf8Value& value) {
        return *value ? *value : "<string conversion failed>";
    }

    void WriteSHM(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();
        String::Utf8Value v8_inputString(isolate, args[0]->TypeOf(isolate));
        printf("%s\n", ToString(v8_inputString));

        Local<Object> bufferObj = args[0].As<Object>();
        void *ptr = malloc(sizeof(bufferObj));
        auto s = v8::SharedArrayBuffer::New(isolate, ptr, sizeof(bufferObj));
        cout << ptr << endl;
        args.GetReturnValue().Set(s);
    }

    void ReadSHM(const FunctionCallbackInfo<Value>& args) {
        Isolate* isolate = args.GetIsolate();
        String::Utf8Value v8_inputString(isolate, args[0]->TypeOf(isolate));
        printf("%s\n", ToString(v8_inputString));
        auto ptr = args[0].As<v8::SharedArrayBuffer>()->GetContents().Data();
        cout << ptr <<endl;
        // int32_t value = args[0] -> Uint32Value(isolate->GetCurrentContext()).ToChecked();
        // cout << value << endl;
        // int *ptr = (int*) value;
        // cout << ptr << endl;
        args.GetReturnValue().SetNull();
    }

    void Initialize(Local<Object> exports) {
        NODE_SET_METHOD(exports, "set", WriteSHM);
        NODE_SET_METHOD(exports, "get", ReadSHM);
    }

    NODE_MODULE(NODE_MODULE_NAME, Initialize);
}

int main() {
    printf("hello world");
    return 0;
}