/*
 * Copyright 2019 Google LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <android/log.h>
#include <jni.h>

#include <memory>

#include "hello_cardboard_app.h"

#define JNI_METHOD(return_type, method_name) \
  JNIEXPORT return_type JNICALL              \
      Java_com_google_cardboard_VrActivity_##method_name


#define JNI_METHOD_WRAPPER(return_type, method_name) \
  JNIEXPORT return_type JNICALL                      \
      Java_com_google_cardboard_CardboardWrapper_##method_name

#define JNI_METHOD_Main_Activity(return_type, method_name) \
  JNIEXPORT return_type JNICALL                      \
      Java_com_google_cardboard_MainActivity_##method_name


namespace {

inline jlong jptr(ndk_hello_cardboard::HelloCardboardApp* native_app) {
  return reinterpret_cast<intptr_t>(native_app);
}

inline ndk_hello_cardboard::HelloCardboardApp* native(jlong ptr) {
  return reinterpret_cast<ndk_hello_cardboard::HelloCardboardApp*>(ptr);
}

JavaVM* javaVm;

}  // anonymous namespace

extern "C" {

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* /*reserved*/) {
  javaVm = vm;
  return JNI_VERSION_1_6;
}

JNI_METHOD(jlong, nativeOnCreate)
(JNIEnv* /*env*/, jobject obj, jobject asset_mgr) {
  return jptr(new ndk_hello_cardboard::HelloCardboardApp(javaVm, obj, asset_mgr));
}

JNI_METHOD_WRAPPER(jlong, nativeOnCreate)
(JNIEnv* /*env*/, jobject obj, jobject asset_mgr) {
  return jptr(new ndk_hello_cardboard::HelloCardboardApp(javaVm, obj, asset_mgr));
}

JNI_METHOD_WRAPPER(void, nativeOnDestroy)
(JNIEnv* /*env*/, jobject /*obj*/, jlong native_app) {
  delete native(native_app);
}

JNI_METHOD_WRAPPER(void, nativeOnSurfaceCreated)
(JNIEnv* env, jobject /*obj*/, jlong native_app) {
  native(native_app)->OnSurfaceCreated(env);
}

JNI_METHOD_WRAPPER(void, nativeOnDrawFrame)
(JNIEnv* /*env*/, jobject /*obj*/, jlong native_app) {
  native(native_app)->OnDrawFrame();
}

JNI_METHOD_WRAPPER(void, nativeOnTriggerEvent)
(JNIEnv* /*env*/, jobject /*obj*/, jlong native_app) {
  native(native_app)->OnTriggerEvent();
}

JNI_METHOD_WRAPPER(void, nativeOnPause)
(JNIEnv* /*env*/, jobject /*obj*/, jlong native_app) {
  native(native_app)->OnPause();
}

JNI_METHOD_WRAPPER(void, nativeOnResume)
(JNIEnv* /*env*/, jobject /*obj*/, jlong native_app) {
  native(native_app)->OnResume();
}

JNI_METHOD_WRAPPER(void, nativeSetScreenParams)
(JNIEnv* /*env*/, jobject /*obj*/, jlong native_app, jint width, jint height) {
  native(native_app)->SetScreenParams(width, height);
}

JNI_METHOD_WRAPPER(void, nativeSwitchViewer)
(JNIEnv* /*env*/, jobject /*obj*/, jlong native_app) {
  native(native_app)->SwitchViewer();
}

JNI_METHOD_Main_Activity(jlong, nativeOnCreate)
(JNIEnv* /*env*/, jobject obj, jobject asset_mgr) {
  return jptr(new ndk_hello_cardboard::HelloCardboardApp(javaVm, obj, asset_mgr));
}


}  // extern "C"