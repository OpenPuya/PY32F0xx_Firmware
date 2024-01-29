================================================================================
                                样例使用说明
================================================================================
功能描述：
此样例演示了在TIM1中使用DMA传输数据的功能，通过DMA从SRAM中搬运数据到ARR寄存器，
实现TIM1周期变化，在TIM1第一次溢出后，PA0会翻转，此时翻转间隔为400ms，DMA开始
搬运数据到TIM1_ARR，第二次PA0翻转间隔为400ms，第三次翻转间隔为100ms，第四次翻
转间隔为200ms，第四次翻转间隔为300ms，此时DMA搬运结束，后续翻转间隔均为300ms
================================================================================
测试环境：
测试用板：PY32F030_STK
MDK版本： 5.28
IAR版本： 9.20
================================================================================
使用步骤：
1. 下载并运行程序
2. 通过逻辑分析仪示波器捕捉PA0上翻转间隔
3. 翻转间隔从400ms，变为100ms，200ms，300ms
4. 变为300ms后，翻转间隔均为300ms

================================================================================
注意事项：


================================================================================