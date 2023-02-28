# esp32-hdc1080-prometheus

The idea is to use the ESP32 connected to the HDC1080 sensor that returns the metrics in the Prometheus way, so we can plug into Grafana, for example.

### Requirements
- 1 ESP32 [board](https://www.aliexpress.com/item/1005002611857804.html?spm=a2g0o.productlist.main.1.341f738aIZQPfx&algo_pvid=6bccb686-4d11-4a8b-826a-7f6ebfa50580&algo_exp_id=6bccb686-4d11-4a8b-826a-7f6ebfa50580-0&pdp_ext_f=%7B%22sku_id%22%3A%2212000021386518349%22%7D&pdp_npi=2%40dis%21BRL%2159.35%2146.92%21%21%21%21%21%40211bf49716711494666402914d077f%2112000021386518349%21sea&curPageLogUid=bRmCcKgmboMO).
- 1 HDC1080 module [sensor](https://www.aliexpress.com/item/32835319730.html?spm=a2g0o.productlist.main.1.2a6d42d2O5uOXk&algo_pvid=992af8ee-ec4a-417d-8229-e9c5ba920535&algo_exp_id=992af8ee-ec4a-417d-8229-e9c5ba920535-0&pdp_ext_f=%7B%22sku_id%22%3A%2212000018098679773%22%7D&pdp_npi=2%40dis%21BRL%2110.22%219.72%21%21%21%21%21%40211bf49716711494895823119d077f%2112000018098679773%21sea&curPageLogUid=LyvwgWtbp5Vw).

### Wiring it together
You can use a protoboard and some jumper wires to connected them. You can use the following:

|ESP32 Board|HDC1080 Module Sensor|
|-----------|---------------------|
|3v3        | 3v3                 |
|GND        | GND                 |
|D21        | SDA                 |
|D22        | SCL                 |

### Install the HDC1080 library
You have to install the HDC1080 library in order to make the sensor work it properly. It's pretty easy, you just need to go to `Tools -> Manage Libraries` on your Arduino IDE and search for `HDC10180` you should see the result as: `ClosedCube HDC1080`, which is [this](https://github.com/closedcube/ClosedCube_HDC1080_Arduino) library here, install the latest version.

### Deploy the code
- Clone this repository.
- Plug your ESP32 board into your computer through the USB port.
- Open the Arduino IDE.
- Open the [esp32-hdc1080-prometheus.ino](./esp32-hdc1080-prometheus.ino) file.
- Change the two variables (`ssid` and `password`) according to your Wifi credentials (lines 11 and 12).
- Press `CTRL + U` or click on the button that deploys the code to your board.
- Now you should be good!

### Test your deployed code
If everything is fine, you should be able to perform a `curl` request to your board and see its output:

```bash
curl http://192.168.X.X/
```

```
# HELP iot_temperature Temperature in celsius
# TYPE iot_temperature gauge
iot_temperature 25.95
# HELP iot_humidity Humidity in percentage
# TYPE iot_humidity gauge
iot_humidity 67.41
```

This is the format that Prometheus can read, interpret it and we should be good to plug into Grafana!!!

### Grafana example
![image](https://user-images.githubusercontent.com/5191469/208089667-a7fe7b96-8093-451d-a3e2-3ae64c9483f1.png)

### Important
If you sometimes get `125C` as temperature, please check this [link](https://github.com/closedcube/ClosedCube_HDC1080_Arduino/issues/11).

### References
- http://www.esp32learning.com/code/esp32-and-hdc1080-humidity-and-temperature-sensor.php
- https://github.com/closedcube/ClosedCube_HDC1080_Arduino
