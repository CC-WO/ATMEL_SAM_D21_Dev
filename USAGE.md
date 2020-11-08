# USAGE

## MPLAB® Harmony Configurator v3

## Load settings

### Launch MHC

Tools -> Embedded -> MPLAB@ Harmony 3 Configurator

### Close MHC

MHC -> Exit

## Generate Code

MHC -> Generate Code

## MHC Settings

### System Settings

![system](img/system.png)

Ports -> Use PORT PLIBをTQFP64に変更する.(Pin Tableからも変更可能)

Processor clockを使ってdelayを使用するう場合はSysTickの設定をする

コード生成の設定などもSystemに集約されているので一度全体に目を通しておくことをお勧めする

### Clock Settings

クロックの設定を行う

MHC -> Tools -> Clock Configuration

基本的には初期設定のまま

![clock](img/clock.png)

外部RTCを使用する場合は以下の設定をする

![clock_rtc1](img/clock_rtc1.png)

外部CRYSTALを使うように設定

![clock_rtc2](img/clock_rtc2.png)

GCLK1を外部CRYSTALを32分周したものに設定

![clock_rtc3](img/clock_rtc3.png)

RTCのクロックソースをGCLK1に設定

### DMA Settings

DMAの設定を行う

MHC -> Tools -> DMA Configuration

SERCOM3をUSARTとして使用する場合は以下の設定をする

![dma](img/dma.png)

### NVIC Settings

割り込みの設定を行う

![nvic](img/nvic.png)

### Pin Settings

ピンの設定を行う

MHC -> MHC -> Pin Configuration

以下のピン設定を行う. 設定を変更するピンのみ記載. (-：設定不可)

|No.|Pin ID|Custom Name    |Function       |Mode    |Direction|Latch|Pull Up|Pull Down|Drive Strength|
|:--|:--   |:--            |:--            |:--     |:--      |:--  |:--    |:--      |:--           |
|3  |PA02  |               |DAC_VOUT       |Analog  |-        |-    |-      |-        |-             |
|11 |PB08  |               |TC4_WO0        |Digital |-        |-    |-      |-        |-             |
|12 |PB09  |               |TC4_WO1        |Digital |-        |-    |-      |-        |-             |
|17 |PA08  |               |SERCOM2_PAD0   |Digital |-        |-    |-      |-        |-             |
|18 |PA09  |               |SERCOM2_PAD1   |Digital |-        |-    |-      |-        |-             |
|19 |PA10  |               |ADC_AIN18      |Analog  |-        |-    |-      |-        |-             |
|32 |PA15  |               |EIC_EXTINT15   |-       |-        |-    |Enable |-        |-             |
|43 |PA22  |               |SERCOM3_PAD0   |Digital |-        |-    |-      |-        |-             |
|44 |PA23  |               |SERCOM3_PAD1   |Digital |-        |-    |-      |-        |-             |
|59 |PB30  |LED            |GPIO           |-       |Out      |-    |-      |-        |-             |

設定後のピンの状態

![pin](img/pin.png)

## Main

MHC Settingsを起こった時点でコード生成したmainファイルをNo.0とする. 以降, 機能を追加していくたびにmainファイルを別で生成する.

デバッグの際は, mainファイルを切り替えて使用する. 基本的には上から順に動作確認することを前提とする.

|No.|Program File      |Description                      |
|:--|:--               |:--                              |
|0  |main.c            |default                          |
|1  |main_gpio.c       |Digital Out, Digital In          |
|2  |main_delay.c      |Delay Function                   |
|3  |main_timer.c      |Timer Function(on TC3)           |
|4  |main_rtc.c        |Real Time Clock Function         |
|5  |main_eic.c        |External Interrupt Function      |
|6  |main_sercom3.c    |USART(on SERCOM3)                |
|7  |main_printf.c     |Stnadard IO Function             |
|8  |main_adc.c        |ADC Function                     |
|9  |main_dac.c        |DAC Function                     |
|10 |main_pwm.c        |PWM Function(on TC4)             |
|11 |main_iic.c        |I2C(on SERCOM4)                  |

## Peripheral Settings

### 1 GPIO

基板のUSER BUTTONを押すと, USER LEDが点灯するサンプル.

PA15の設定のみ変更し, コード生成を行う. 初期では状態変化割り込みとしているが汎用の入力ピンに変更するため.

|No.|Pin ID|Custom Name    |Function       |Mode    |Direction|Latch|Pull Up|Pull Down|Drive Strength|
|:--|:--   |:--            |:--            |:--     |:--      |:--  |:--    |:--      |:--           |
|32 |PA15  |BUTTON         |GPIO           |-       |In       |-    |-      |-        |-             |

他のサンプルを試す場合は元に戻す

### 2 Delay

Systickを利用したDelay関数で100msのタイマーを作成し, LEDをToggleさせる

### 3 Timer

Available Components -> Periherals -> TC -> TC3を選択

TC3を利用した100msのタイマーを作成し, LEDをToggleさせる

TC3を以下のように設定する

![TC3](img/TC3.png)

### 4 RTC

Available Components -> Periherals -> TC -> RTCを選択

RTCを利用した1sのタイマーを作成し, LEDをToggleさせる

RTCを以下のように設定する

![rtc](img/rtc.png)

### 5 EIC

Available Components -> Periherals -> EIC -> EICを選択

状態変化割り込みでボタンの変化を読み取る

EICを以下のように設定する

![eic](img/eic.png)

### 6 SERCOM UART

Available Components -> Periherals -> SERCOM -> SERCOM3を選択

SERCOM3をUARTに設定し, TermianlでSerialデバッグをする

SERCOM3を以下のように設定する

![SERCOM3](img/SERCOM3.png)

Terminalで確認する

![SERCOM3_HelloWorld](img/SERCOM3_HelloWorld.png)

### 7 SERCOM printf

Available Components -> Tools-> STDIOを選択

printfのputc, getcをSERCOM3にリダイレクトするように設定する

SERCOM3とSTDIOのUARTピンをそれぞれ接続する

![STDIO](img/STDIO.png)

### 8 ADC

Available Components -> Periherals -> ADC -> ADCを選択

MHC -> MHC -> ADC Configurationを選択

PA10をADC入力(AIN18)として使用する

ADCの設定をする

![adc1](img/adc1.png)

![adc2](img/adc2.png)

Terminalで確認する

![adc3](img/adc3.png)

### 9 DAC

Available Components -> Periherals -> DAC -> DACを選択

PA02をDAC出力として設定する

DACの設定をする

![dca](img/dac.png)

### 10 PWM

Available Components -> Periherals -> TC -> TC4を選択

PB08, PB09をTC_WO4, TC_WO1として設定する

TC4の設定をする

TC4を以下のように設定する

![TC4](img/TC4.png)

### 11 I2C