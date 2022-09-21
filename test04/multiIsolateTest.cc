#include <node.h>
#include <uv.h>
#include <stdio.h>
#include <stdlib.h>



namespace multiIsolateTest {
    using v8::FunctionCallbackInfo;
    using v8::Local;
    using v8::Value;
    using v8::String;
    using v8::Number;
    using v8::Isolate;
    using v8::Context;
    using v8::Object;


    
    void Method(const FunctionCallbackInfo<Value>&args) {
        uv_loop_t *loop;
        loop = uv_default_loop();
        Isolate* isolate_01 = args.GetIsolate();
        auto threadID = node::AllocateEnvironmentThreadId();
        auto tracingController = node::GetTracingController();
        
        auto node_multiIsolatePlatform = node::CreatePlatform(threadID.id, tracingController);
        auto pageAllocator = node_multiIsolatePlatform->GetPageAllocator();
        auto isolate_02_allocator = node::ArrayBufferAllocator::Create();
        Isolate* isolate_02 =  node::NewIsolate(isolate_02_allocator.get(), loop, node_multiIsolatePlatform);
        

        isolate_01->Enter();
        args.GetReturnValue().SetNull();
        isolate_01->Exit();
    }

    void Initialize(Local<Object> exports) {
        NODE_SET_METHOD(exports, "multiIsolateTest", Method);
    }

    NODE_MODULE(NODE_MODULE_NAME, Initialize);
}