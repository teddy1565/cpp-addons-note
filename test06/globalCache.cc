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
    using v8::Function;
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
        // printf("%s\n", ToString(v8_inputString));

        Local<Function> bufferObj = args[0].As<Function>();
        void *ptr = malloc(sizeof(bufferObj)*1000);
        if (ptr == NULL) {
            cout << "fail" << endl;
        }
        auto sharedArrayBuffer = v8::SharedArrayBuffer::New(isolate, ptr, sizeof(bufferObj)*10000);
        // cout << ptr << endl;
        // cout << sizeof(bufferObj) << endl;
        args.GetReturnValue().Set(sharedArrayBuffer);
    }

    void ReadSHM(const FunctionCallbackInfo<Value>& args) {
        
        Isolate* isolate = args.GetIsolate();
        String::Utf8Value v8_inputString(isolate, args[0]->TypeOf(isolate));
        printf("%s\n", ToString(v8_inputString));
        auto arrayBuffer = args[0].As<v8::SharedArrayBuffer>()->GetBackingStore();

        auto length = arrayBuffer->ByteLength();
        void *func_address = arrayBuffer->Data();
        cout << func_address << endl;
        free(func_address);
        // func();
        // func_ptr = func_address;

        // v8::Local<v8::Value>::New(isolate, ptr);
        // auto m = v8::SharedArrayBuffer(bufferContents.Data())

        // v8::Local<v8::Value> func_template_argv[1];
        // auto v = v8::Local<v8::Value>::New(isolate, ptr);
        // auto m = v8::Object::New(isolate);
        // auto callback = v8::FunctionCallback();
        // auto func_template = v8::Function::New(isolate->GetCurrentContext(), callback, );

        
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