#include <napi.h>
#include <uv.h>
#include <v8.h>
#include <napi.h>
#include <uv.h>

#include "InteractiveNotifications.h"
#include <malloc.h>
#include <windows.h>
#include <stdio.h>
#include <locale>
#include <codecvt>

typedef void (__stdcall *f_funci)();

Napi::Value RegisterAppForNotificationSupport(const Napi::CallbackInfo& info)
{
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);

	if (info.Length() < 2 || !info[0].IsString() || !info[1].IsString())
	{
		Napi::TypeError::New(env, "Invalid arguments, expected arguments are: shortcut name[string], app id [string]").ThrowAsJavaScriptException();
		return env.Null();
	}

	std::string shortcutHandle = info[0].As<Napi::String>().Utf8Value();
	std::string appIdHandle = info[1].As<Napi::String>().Utf8Value();

	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> convert;
    const wchar_t* shortcutStringValue = convert.from_bytes(shortcutHandle).c_str();
	const wchar_t* appIdStringValue = convert.from_bytes(appIdHandle).c_str();

	HRESULT hr = InteractiveNotifications::RegisterAppForNotificationSupport((PCWSTR)*shortcutStringValue, (PCWSTR)*appIdStringValue);

	if (hr != S_OK)
	{
		std::string errorMessage = "RegisterAppForNotificationsSupport Failed with error code:" + std::to_string(hr);
		Napi::TypeError::New(env, errorMessage).ThrowAsJavaScriptException();
		return env.Null();
	}
}

Napi::Value RegisterComServer(const Napi::CallbackInfo& info)
{
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	InteractiveNotifications::RegisterComServer();
	return env.Null();
}

Napi::Value RegisterActivator(const Napi::CallbackInfo& info)
{
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	InteractiveNotifications::RegisterActivator();
	return env.Null();
}

Napi::Value UnregisterActivator(const Napi::CallbackInfo& info)
{
	Napi::Env env = info.Env();
	Napi::HandleScope scope(env);
	InteractiveNotifications::UnregisterActivator();
	return env.Null();
}

Napi::Object init(Napi::Env env, Napi::Object exports) {
  // TODO: Make sure that this is necesarry..
  HRESULT hr = CoInitializeEx(NULL, COINITBASE_MULTITHREADED);

  exports.Set(Napi::String::New(env, "registerComServer"), Napi::Function::New(env, RegisterComServer));
  exports.Set(Napi::String::New(env, "registerAppForNotificationSupport"), Napi::Function::New(env, RegisterAppForNotificationSupport));
  exports.Set(Napi::String::New(env, "registerActivator"), Napi::Function::New(env, RegisterActivator));
  exports.Set(Napi::String::New(env, "unregisterActivator"), Napi::Function::New(env, UnregisterActivator));
  return exports;
}

NODE_API_MODULE(notifications_bindings, init)