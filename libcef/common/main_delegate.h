// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CEF_LIBCEF_COMMON_MAIN_DELEGATE_H_
#define CEF_LIBCEF_COMMON_MAIN_DELEGATE_H_
#pragma once

#include <string>

#include "libcef/common/content_client.h"
#include "include/cef_app.h"

#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "content/public/app/content_main_delegate.h"

namespace content {
class BrowserMainRunner;
}

class CefContentBrowserClient;
class CefContentRendererClient;
class CefContentPluginClient;
class CefContentUtilityClient;
class MessageLoop;

class CefMainDelegate : public content::ContentMainDelegate {
 public:
  explicit CefMainDelegate(CefRefPtr<CefApp> application);
  virtual ~CefMainDelegate();

  virtual bool BasicStartupComplete(int* exit_code) OVERRIDE;
  virtual void PreSandboxStartup() OVERRIDE;
  virtual void SandboxInitialized(const std::string& process_type) OVERRIDE;
  virtual int RunProcess(
      const std::string& process_type,
      const content::MainFunctionParams& main_function_params) OVERRIDE;
  virtual void ProcessExiting(const std::string& process_type) OVERRIDE;
#if defined(OS_MACOSX)
  virtual bool ProcessRegistersWithSystemProcess(
      const std::string& process_type) OVERRIDE;
  virtual bool ShouldSendMachPort(const std::string& process_type) OVERRIDE;
  virtual bool DelaySandboxInitialization(
      const std::string& process_type) OVERRIDE;
#elif defined(OS_POSIX)
  virtual content::ZygoteForkDelegate* ZygoteStarting() OVERRIDE;
  virtual void ZygoteForked() OVERRIDE;
#endif  // OS_MACOSX

  // Shut down the browser runner.
  void ShutdownBrowser();

  CefContentBrowserClient* browser_client() { return browser_client_.get(); }
  CefContentClient* content_client() { return &content_client_; }

 private:
  void InitializeContentClient(const std::string& process_type);
  void InitializeResourceBundle();

  scoped_ptr<content::BrowserMainRunner> browser_runner_;
  scoped_ptr<CefContentBrowserClient> browser_client_;
  scoped_ptr<CefContentRendererClient> renderer_client_;
  scoped_ptr<CefContentPluginClient> plugin_client_;
  scoped_ptr<CefContentUtilityClient> utility_client_;
  CefContentClient content_client_;

  DISALLOW_COPY_AND_ASSIGN(CefMainDelegate);
};

#endif  // CEF_LIBCEF_COMMON_MAIN_DELEGATE_H_
