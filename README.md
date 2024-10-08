# PageBuilder v1.2
Component for ESP-IDF framework, compatibility only with ESP32.
PageBuilder it's software for fast making and prototyping ESP32 projects, using block and widgets.
Uses the following ESP-IDF dependencies and C++ STD.

## v1.2
Added XML queue.
Now you can choose between STA and AP wifi mode.

## XML queue
For optimize server request and don't spam, i use queue for xml requests.
IN/INOUT requests pushing front, OUT requests pushing back.
Every ```delta time``` server make one request from queue.
![alt text](https://github.com/urlagushka/esp32-pagebuilder/blob/main/xmlqueue.png)

## Widget types
### LiveLabel
Label that updates in runtime without update page.

Syntax example:
```cpp
// LiveLabel(const Block * src, c_str_ref_t label, std::size_t dtime)
// 1. Parent block
// 2. Label
// 3. Delta time in ms

std::string addf()
{
    return "to put data";
}

class MyHTTPServer:
    public kb::HTTPServer
{
    using kb::HTTPServer::HTTPServer;
    public:
        void setup_page() override
        {
            kb::PageBuilder page_ex(kb::get_style(), 100);
            mypage.set_title("Dashboard");
            mypage.set_header("LiveLavel Example");
            
            auto block_ex = new kb::Block("HeaderEX", InfoEX);
            auto livelabel_ex = new kb::LiveLabel(block_ex, "Label", 100);
            block_ex->add_widget(livelabel_ex);
            bind(livelabel_ex, addf);

            page_ex.add_block(livelabel_ex);
            page_ = page_ex.get_page();

            delete block_ex;
            delete livelabel_ex;
        }
};
```

### ButtonField
Button with input field for activate some function with input.

Syntax example:
```cpp
// ButtonField(const Block *, const std::string &, const std::string &)
// 1. Parent block
// 2. Article
// 3. Label

void addf(const std::string & rhs)
{
    ESP_LOG("EXAMPLE", "BUTTON PRESSED, recieved following data: %s", rhs.c_str());
}

class MyHTTPServer:
    public kb::HTTPServer
{
    using kb::HTTPServer::HTTPServer;
    public:
        void setup_page() override
        {
            kb::PageBuilder page_ex(kb::get_style(), 100);
            mypage.set_title("Dashboard");
            mypage.set_header("ButtonField Example");
            
            auto block_ex = new kb::Block("HeaderEX", InfoEX);
            auto buttonfield_ex = new kb::ButtonField(block_ex, "Artice", "Label");
            block_ex->add_widget(buttonfield_ex);
            bind(buttonfield_ex, addf);

            page_ex.add_block(block_ex);
            page_ = page_ex.get_page();

            delete block_ex;
            delete buttonfield_ex;
        }
};
```

### Button
Simple button for activate some function.

Syntax example:
```cpp
// Button(const Block *, const std::string &)
// 1. Parent block
// 2. Label

void addf(const std::string &)
{
    ESP_LOG("EXAMPLE", "BUTTON PRESSED");
}

class MyHTTPServer:
    public kb::HTTPServer
{
    using kb::HTTPServer::HTTPServer;
    public:
        void setup_page() override
        {
            kb::PageBuilder page_ex(kb::get_style(), 100);
            mypage.set_title("Dashboard");
            mypage.set_header("Button Example");
            
            auto block_ex = new kb::Block("HeaderEX", InfoEX);
            auto button_ex = new kb::Button(block_ex, "Label");
            block_ex->add_widget(button_ex);
            bind(button_ex, addf);

            page_ex.add_block(block_ex);
            page_ = page_ex.get_page();

            delete block_ex;
            delete button_ex;
        }
};
```

## Full main.cpp example
```cpp
#include "freeRTOS\freeRTOS.h"
#include "freeRTOS\task.h"

#include "http-server.hpp"
#include "page-builder.hpp"
#include "button-field.hpp"
#include "button.hpp"
#include "live-label.hpp"
#include "stylesheet.hpp"

#include <string>

class MyHTTPServer:
    public kb::HTTPServer
{
    using kb::HTTPServer::HTTPServer;
    public:
        void setup_page() override
        {
            kb::PageBuilder mypage(kb::get_style(), 100); // Delta time to send request
            mypage.set_title("Dashboard");
            mypage.set_header("DashBoard");

            auto stepper = new kb::Block("StepperMotor", "Stepper motor control");
            auto on = new kb::Button(stepper, "ON");
            auto off = new kb::Button(stepper, "OFF");
            auto step_set = new kb::ButtonField(stepper, "Step control", "SET");
            auto speed_set = new kb::ButtonField(stepper, "Speed control", "SET");
            auto step_get = new kb::LiveLavel(stepper, "Step", 500); // Delta time to add in XML queue
            auto speed_get = new kb::LiveLabel(stepper, "Speed", 500);

            stepper->add_widget(on);
            stepper->add_widget(off);
            stepper->add_widget(step_set);
            stepper->add_widget(speed_set);
            stepper->add_widget(step_get);
            stepper->add_widget(speed_get);

            mypage.add_block(stepper);

            bind(on, some_function);
            bind(off, some_function);
            bind(x, some_function);
            bind(y, some_function);
            bind(z, some_function);

            auto sensors = new kb::Block("Sensors", "Sensor states");
            auto encoder = new kb::LiveLavel(sensors, "Encoder", 500);
            auto left_cap = new kb::LiveLabel(sensors, "Left cap", 500);
            auto middle_cap = new kb::LiveLabel(sensors, "Middle cap", 500);
            auto right_cap = new kb::LiveLabel(sensors, "Right cap", 500);

            sensors->add_widget(encoder);
            sensors->add_widget(left_cap);
            sensors->add_widget(middle_cap);
            sensors->add_widget(right_cap);
            
            mypage.add_block(sensors);

            bind(encoder, some_function);
            bind(left_cap, some_function);
            bind(middle_cap, some_function);
            bind(right_cap, some_function);

            page_ = mypage.get_page();
            
            delete stepper;
            delete on;
            delete off;
            delete step_set;
            delete speed_set;
            delete step_get;
            delete speed_get;
            
            delete sensors;
            delete encoder;
            delete left_cap;
            delete middle_cap;
            delete right_cap;
        }
};

extern "C" void app_main(void)
{
    MyHTTPServer web("SSID", "PASSWORD", kb::WIFITYPE::AP); // ::AP || ::STA
    ESP_ERROR_CHECK(web.init());
    ESP_ERROR_CHECK(web.connect());
    web.setup_page();
    ESP_ERROR_CHECK(web.start());

    while(1)
    {
        vTaskDelay(1);
    }
}
```

Result:
![alt text](https://github.com/urlagushka/esp32-pagebuilder/blob/main/dashboard.png)
