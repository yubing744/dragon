/*
* Copyright 2013 the original author or authors.
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

/**********************************************************************
 * Author:      Owen Wu/wcw/yubing
 * Email:       yubing744@163.com
 * Created:     2013/09/28
 **********************************************************************/

#include <wrl/client.h>
#include <d3d11_1.h>
#include <DirectXMath.h>
#include <memory>
#include <agile.h>
#include <ppltasks.h>

// Implements AppLauncher 
// 
#include <com/dragon3d/launcher/AppLauncher.h>

#include <com/dragon3d/framework/Application.h>
#include <com/dragon3d/output/graphics/GraphicsDevice.h>
#include <dragon/lang/Throwable.h>
#include <dragon/util/ArrayList.h>
#include <dragon/util/logging/Logger.h>

Import dragon::lang;
Import dragon::util::logging;
Import com::dragon3d::framework;
Import com::dragon3d::input;
Import com::dragon3d::output;
Import com::dragon3d::output::graphics;

Import Windows::ApplicationModel;
Import Windows::ApplicationModel::Core;
Import Windows::ApplicationModel::Activation;
Import Windows::UI::Core;
Import Windows::System;
Import Windows::Foundation;
Import Windows::Graphics::Display;
Import concurrency;

static Logger* logger = Logger::getLogger("com::dragon3d::launcher::AppLauncher#wp8", INFO);

/**
 * dragon3d wp8 app proxy view
 */
ref class Dragon3DWp8AppProxyView sealed : public Windows::ApplicationModel::Core::IFrameworkView, 
    Windows::ApplicationModel::Core::IFrameworkViewSource {
public:
    Dragon3DWp8AppProxyView(Platform::IntPtr appPtr) :
        m_windowVisible(true){
        this->app = reinterpret_cast<Application*>(appPtr.ToInt32());
    }

    virtual ~Dragon3DWp8AppProxyView() {}

public:
    virtual Windows::ApplicationModel::Core::IFrameworkView^ CreateView() {
        return this;
    }

public:    

    // IFrameworkView 方法。
    virtual void Initialize(Windows::ApplicationModel::Core::CoreApplicationView^ applicationView) {
        applicationView->Activated +=
            ref new TypedEventHandler<CoreApplicationView^, IActivatedEventArgs^>(this, &Dragon3DWp8AppProxyView::OnActivated);

        CoreApplication::Suspending +=
            ref new EventHandler<SuspendingEventArgs^>(this, &Dragon3DWp8AppProxyView::OnSuspending);

        CoreApplication::Resuming +=
            ref new EventHandler<Platform::Object^>(this, &Dragon3DWp8AppProxyView::OnResuming);
    }

    virtual void SetWindow(Windows::UI::Core::CoreWindow^ window) {
        window->VisibilityChanged +=
            ref new TypedEventHandler<CoreWindow^, VisibilityChangedEventArgs^>(this, &Dragon3DWp8AppProxyView::OnVisibilityChanged);

        window->Closed += 
            ref new TypedEventHandler<CoreWindow^, CoreWindowEventArgs^>(this, &Dragon3DWp8AppProxyView::OnWindowClosed);

        window->PointerPressed +=
            ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &Dragon3DWp8AppProxyView::OnPointerPressed);

        window->PointerMoved +=
            ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &Dragon3DWp8AppProxyView::OnPointerMoved);

        window->PointerReleased +=
            ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &Dragon3DWp8AppProxyView::OnPointerReleased);
    }

    virtual void Load(Platform::String^ entryPoint) {
        this->app->onStart();
    }

    virtual void Run() {
        while (!app->isExit()) {
            if (m_windowVisible) {
                CoreWindow::GetForCurrentThread()->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessAllIfPresent);

                app->runLoop();
            } else {
                CoreWindow::GetForCurrentThread()->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessOneAndAllPending);
            }
        }
    }


    virtual void Uninitialize() {

    }

protected:
    // 事件处理程序。
    void OnActivated(Windows::ApplicationModel::Core::CoreApplicationView^ applicationView, Windows::ApplicationModel::Activation::IActivatedEventArgs^ args) {
        CoreWindow::GetForCurrentThread()->Activate();
    }

    void OnSuspending(Platform::Object^ sender, Windows::ApplicationModel::SuspendingEventArgs^ args){
        // 在请求延期后异步保存应用程序状态。保留延期
        // 表示应用程序正忙于执行挂起操作。
        // 请注意，延期不是无限期的。在大约五秒后，
        // 将强制应用程序退出。
        SuspendingDeferral^ deferral = args->SuspendingOperation->GetDeferral();
        
        // TODO replace for app handler
        // m_renderer->ReleaseResourcesForSuspending();

        create_task([this, deferral]() {
            // 在此处插入代码。

            deferral->Complete();
        });
    }

    void OnResuming(Platform::Object^ sender, Platform::Object^ args){
        // 还原在挂起时卸载的任何数据或状态。默认情况下，
        // 在从挂起中恢复时，数据和状态会持续保留。请注意，
        // 如果之前已终止应用程序，则不会发生此事件。
        
        // TODO replace code for app
        // m_renderer->CreateWindowSizeDependentResources();
    }

    void OnWindowClosed(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::CoreWindowEventArgs^ args){
        app->exit();
    }

    void OnVisibilityChanged(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::VisibilityChangedEventArgs^ args){
        m_windowVisible = args->Visible;
    }

    void OnPointerPressed(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::PointerEventArgs^ args){
        // 在此处插入代码。
    }

    void OnPointerMoved(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::PointerEventArgs^ args){
        // 在此处插入代码。
    }

    void OnPointerReleased(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::PointerEventArgs^ args){
        // 在此处插入代码。
    }

private:
    Application* app;
    bool m_windowVisible;
};

/**
 * launch a app.
 * 
 * @param app [description]
 */
void Dragon3DLaunchApp(Application* app) {
    logger->info("launchApp");

    // input
    InputManager* inputManager = new InputManager(); 
    app->setInputManager(inputManager);

    // ouput
    OutputManager* outputManager = new OutputManager();

    {
        // add graphics device
        GraphicsDevice* graphicsDevice = new GraphicsDevice();
        outputManager->registerDevice(graphicsDevice);
    }

    app->setOutputManager(outputManager);

    auto direct3DApplicationSource = ref new Dragon3DWp8AppProxyView(Platform::IntPtr(app));
    CoreApplication::Run(direct3DApplicationSource);
}

/**
 * terminate a app.
 * 
 * @param app [description]
 */
void Dragon3DTerminateApp(Application* app) {
    app->exit();
}