// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "android_webview/browser/aw_dev_tools_discovery_provider.h"

#include "android_webview/browser/browser_view_renderer.h"
#include "base/json/json_writer.h"
#include "base/memory/ptr_util.h"
#include "base/strings/stringprintf.h"
#include "base/strings/utf_string_conversions.h"
#include "base/values.h"
#include "content/public/browser/devtools_agent_host.h"
#include "content/public/browser/web_contents.h"

using content::DevToolsAgentHost;
using content::WebContents;

namespace {

std::string GetViewDescription(WebContents* web_contents) {
  android_webview::BrowserViewRenderer* bvr =
      android_webview::BrowserViewRenderer::FromWebContents(web_contents);
  if (!bvr) return "";
  base::DictionaryValue description;
  description.SetBoolean("attached", bvr->attached_to_window());
  description.SetBoolean("visible", bvr->IsVisible());
  gfx::Rect screen_rect = bvr->GetScreenRect();
  description.SetInteger("screenX", screen_rect.x());
  description.SetInteger("screenY", screen_rect.y());
  description.SetBoolean("empty", screen_rect.size().IsEmpty());
  if (!screen_rect.size().IsEmpty()) {
    description.SetInteger("width", screen_rect.width());
    description.SetInteger("height", screen_rect.height());
  }
  std::string json;
  base::JSONWriter::Write(description, &json);
  return json;
}

content::DevToolsAgentHost::List GetDescriptors() {
  DevToolsAgentHost::List agent_hosts = DevToolsAgentHost::GetOrCreateAll();
  for (auto& agent_host : agent_hosts) {
    agent_host->SetDescriptionOverride(
        GetViewDescription(agent_host->GetWebContents()));
  }
  return agent_hosts;
}

}  // namespace

namespace android_webview {

// static
void AwDevToolsDiscoveryProvider::Install() {
  content::DevToolsAgentHost::AddDiscoveryProvider(base::Bind(&GetDescriptors));
}

AwDevToolsDiscoveryProvider::AwDevToolsDiscoveryProvider() {
}

AwDevToolsDiscoveryProvider::~AwDevToolsDiscoveryProvider() {
}

}  // namespace android_webview