// VidyoAddon.cc
#include <node.h>
#include "Lmi/VidyoClient/VidyoClientElectron.h"
#include "Lmi/Os/LmiMallocAllocator.h"
#include <string>

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

void VidyoAddonInit(const FunctionCallbackInfo<Value>& args)
{
  Isolate* isolate = args.GetIsolate();

  if (VidyoClientElectronInit())
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, "Succeed").ToLocalChecked());
  else
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, "Fail").ToLocalChecked());
}

void VidyoAddonUninit(const FunctionCallbackInfo<Value>& args)
{
  VidyoClientElectronUninit();
}

void VidyoAddonDispatch(const FunctionCallbackInfo<Value>& args)
{
  v8::Local<v8::Context> context = args.GetIsolate()->GetCurrentContext();
  Isolate* isolate = args.GetIsolate();
  //v8::String::Utf8Value string(value); to v8::String::Utf8Value string(v8::Isolate::GetCurrent(), value);
  String::Utf8Value data(v8::Isolate::GetCurrent(), args[0]->ToString(context).ToLocalChecked());
  std::string request(*data);
  LmiString requestSt;
  LmiString responseSt;
  LmiAllocator *alloc;

  alloc = LmiMallocAllocatorGetDefault();
  LmiStringConstructCStr(&requestSt, request.c_str(), alloc);
  LmiStringConstructDefault(&responseSt, alloc);
  VidyoClientElectronDispatch(&requestSt, &responseSt);

  args.GetReturnValue().Set(String::NewFromUtf8(isolate, LmiStringCStr(&responseSt)).ToLocalChecked());
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "VidyoAddonInit", VidyoAddonInit);
  NODE_SET_METHOD(exports, "VidyoAddonUninit", VidyoAddonUninit);
  NODE_SET_METHOD(exports, "VidyoAddonDispatch", VidyoAddonDispatch);
}

NODE_MODULE(VidyoAddon, init)
