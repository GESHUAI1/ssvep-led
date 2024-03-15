## 2024年1月10日

### 1、配合外壳丝印修改通道

#### 1.1、外壳丝印

<img src="C:\Users\econ\AppData\Roaming\Typora\typora-user-images\image-20240110201532919.png" alt="image-20240110201532919"  /><img src="C:\Users\econ\AppData\Roaming\Typora\typora-user-images\image-20240110201836590.png" alt="image-20240110201836590" style="zoom: 67%;" />

#### 1.2、修改程序

1.2.1、通道指示灯函数【Channel_LED_Control】

1.2.2、通道使能函数【LED_Channel_Control】

1.2.3、频率控制函数【LED_Freq_Control】

主要修改switch中case后面的数字即可

1.2.4、修改函数【Main_Loop_Add】中

![image-20240110202650861](C:\Users\econ\AppData\Roaming\Typora\typora-user-images\image-20240110202650861.png)

![image-20240111145620641](C:\Users\econ\AppData\Roaming\Typora\typora-user-images\image-20240111145620641.png)

1.2.5、修改定时器程序【HAL_TIM_PeriodElapsedCallback】



