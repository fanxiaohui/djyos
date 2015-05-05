//----------------------------------------------------
// Copyright (c) 2014, SHENZHEN PENGRUI SOFT CO LTD. All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:

// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//-----------------------------------------------------------------------------
// Copyright (c) 2014 ����Ȩ�����������������޹�˾���С�����Ȩ�˱���һ��Ȩ����
//
// �����Ȩ�����ʹ���߷������������������£�����ʹ����ʹ�ü���ɢ����
// ������װԭʼ�뼰����λ��ִ����ʽ��Ȩ�������۴˰�װ�Ƿ񾭸�����Ȼ��
//
// 1. ���ڱ�����Դ�������ɢ�������뱣�������İ�Ȩ���桢�������б�����
//    ������������������
// 2. ���ڱ��׼�����λ��ִ����ʽ����ɢ���������������ļ��Լ�������������
//    ��ɢ����װ�е�ý�鷽ʽ����������֮��Ȩ���桢�������б����Լ�����
//    ������������

// �����������������Ǳ�������Ȩ�������Լ�����������״��"as is"���ṩ��
// ��������װ�����κ���ʾ��Ĭʾ֮�������Σ������������ھ��������Լ��ض�Ŀ
// �ĵ�������ΪĬʾ�Ե�������Ȩ�����˼�������֮�����ߣ������κ�������
// ���۳�����κ��������塢���۴�����Ϊ���Լ��ϵ���޹�ʧ������������Υ
// Լ֮��Ȩ��������ʧ������ԭ��ȣ����𣬶����κ���ʹ�ñ�������װ��������
// �κ�ֱ���ԡ�����ԡ�ż���ԡ������ԡ��ͷ��Ի��κν�����𺦣�����������
// �������Ʒ������֮���á�ʹ����ʧ��������ʧ��������ʧ��ҵ���жϵȵȣ���
// �����κ����Σ����ڸ���ʹ���ѻ���ǰ��֪���ܻ���ɴ����𺦵���������Ȼ��
//-----------------------------------------------------------------------------
//========================================================
// �ļ�ģ��˵��:
// omapl138��ʱ����������
// �ļ��汾: v1.00
// ������Ա: lst
// ����ʱ��: 2011.06.01
// Copyright(c) 2011-2011  ���������������޹�˾
//========================================================
// �����޸ļ�¼(���µķ�����ǰ��):
//  <�汾��> <�޸�����>, <�޸���Ա>: <�޸Ĺ��ܸ���>
//========================================================
//���磺
// V1.02 2004-07-14, ����: ���պ������ӶԱ��ĳ�����Ч��У��


//omapl138�Ķ�ʱ�����ܼ���:
//�и�64λ��ʱ����ÿ��64λ��ʱ���ֿ�����Ϊ2��32λ��ʱ��(t12��t34)��
//Timer64P1��64λģʽ����Ϊ���Ź�ʹ�ã���32λģʽ�����ԡ�
//32λ��ʽ���ַ�Ϊ�������ӳɾջ����ķ�ʽ�Ͷ���32λ��ʽ��
//�ջ�����ʽ��ʵ�����ǰ�t34��Ϊt12��Ԥ��Ƶ����
//����ģʽ�£�t34��һ��4bit��Ԥ��Ƶ����t12û�С�
//�Ǿջ���ģʽ�£�t12��8��32λ�ıȽϼĴ���

tagTimerReg *__timer_get_timer_reg(u32 t64_no)
{
    switch(t64_no)
    {
        case 0:
            return (tagTimerReg *)g_ptTimer0Reg;
        case 1:
            return (tagTimerReg *)g_ptTimer1Reg;
        case 2:
            return (tagTimerReg *)g_ptTimer2Reg;
        case 3:
            return (tagTimerReg *)g_ptTimer3Reg;
        default:
            return NULL;
    }
}


//----����64����˫32λģʽ-----------------------------------------------------
//����: ���ö�ʱ��������64λģʽ����˫32λģʽ�¡�
//����: t64_no,�����õ�64λtimer��0~3
//      mode,����ģʽ��0=64bit��1=˫32ģʽ��2=64λ���Ź�(��t64-1),3=32λ����ʽ��
//����: ��
//-----------------------------------------------------------------------------
void timer_counter_len_set(u32 t64_no,ufast_t mode)
{
    tagTimerReg * timer;
    if(t64_no > 3)
        return;
    timer = __timer_get_timer_reg(t64_no);
    timer->TGCR &= ~((u32)0x0c);
    timer->TGCR |= mode<<2;
}

//----ʹ��/��ֹ�ж�------------------------------------------------------------
//����: ʹ�ܻ��ֹtimer�����жϣ�ע�⣬����ֻ�ǿ���timerģ�鱾����Ҫ����Ӧtimer
//      �жϣ���Ҫ���жϿ�������Ҳʹ����Ӧ���ж��ߡ�
//����: t64_no,�����õ�64λtimer��0~3
//      msk,���������жϹ���:
//          =EVTINTEN34  t34�¼������ж�
//          =PRDINTEN34  t34����ƥ���ж�
//          =EVTINTEN12  t12�¼������ж�
//          =PRDINTEN12  t12����ƥ���ж�
//      en��false=��ֹ��true=ʹ��
//����: ��
//-----------------------------------------------------------------------------
void timer_int_ctrl(u32 t64_no,u32 msk,bool_t en)
{
    tagTimerReg * timer;
    if(t64_no > 3)
        return;
    timer = __timer_get_timer_reg(t64_no);
    if(en)
        timer->INTCTLSTAT |= msk;
    else
        timer->INTCTLSTAT &= ~msk;
}

//----����ʱ��Դ---------------------------------------------------------------
//����: ���ö�ʱ����ʱ��Դ���ڲ���������ⲿ���š�
//����: t64_no,�����õ�64λtimer��0~3
//      sub�������õ����ĸ�32λ��ʱ��:0=t12����64λģʽ��1=t34
//      src��ʱ��Դ��0=�ڲ�ʱ�ӣ�1=�ⲿʱ��
//����: ��
//-----------------------------------------------------------------------------
void timer_set_clksrc(u32 t64_no,u32 sub,u32 src)
{
    tagTimerReg * timer;
    u32 offset;
    if(t64_no > 3)
        return;
    timer = __timer_get_timer_reg(t64_no);
    if(sub ==0 )
        offset = CLKSRC12_64_OFF;
    else
        offset = CLKSRC34_OFF;

    if(src == 0)
        timer->TCR &= ~(u32)(1<<offset);
    else
        timer->TCR |= 1<<offset;
}

//----���ù���ģʽ-------------------------------------------------------------
//����: ���ö�ʱ���Ĺ���ģʽ��
//����: t64_no,�����õ�64λtimer��0~3
//      sub�������õ����ĸ�32λ��ʱ��:0=t12��1=t34
//      mode,����ģʽ��0=��������1=���μ�����2=���ڹ�����3=���ڹ���������
//����: ��
//-----------------------------------------------------------------------------
void timer_set_mode(u32 t64_no,u32 sub,u32 mode)
{
    tagTimerReg * timer;
    u32 offset;
    if(t64_no > 3)
        return;
    timer = __timer_get_timer_reg(t64_no);
    if(sub ==0 )
        offset = ENAMODE12_OFF;
    else
        offset = ENAMODE34_OFF;

    timer->TCR &= ~(u32)(0x3<<offset);
    timer->TCR |= mode<<offset;
}

//----���ö�ʱ����-------------------------------------------------------------
//����: ���ö�ʱ����
//����: t64_no,�����õ�64λtimer��0~3
//      sub�������õ����ĸ�32λ��ʱ��:0=t12��1=t34
//      value,����ֵ
//����: ��
//-----------------------------------------------------------------------------
void timer_set_Period(u32 t64_no,u32 sub,u32 value)
{
    tagTimerReg * timer;
    if(t64_no > 3)
        return;
    timer = __timer_get_timer_reg(t64_no);
    if(sub == 0)
        timer->PRD12 = value;
    else
        timer->PRD34 = value;
}

//----������������-------------------------------------------------------------
//����: �����������ڣ�����ʱ�����������������ط�ʽʱ����
//����: t64_no,�����õ�64λtimer��0~3
//      sub�������õ����ĸ�32λ��ʱ��:0=t12��1=t34
//      value,����ֵ
//����: ��
//-----------------------------------------------------------------------------
void timer_set_reload(u32 t64_no,u32 sub,u32 value)
{
    tagTimerReg * timer;
    if(t64_no > 3)
        return;
    timer = __timer_get_timer_reg(t64_no);
    if(sub == 0)
        timer->REL12 = value;
    else
        timer->REL34 = value;
}

//----ֹͣ��ʱ��-------------------------------------------------------------
//����: ֹͣ��ʱ��
//����: t64_no,�����õ�64λtimer��0~3
//      sub�������õ����ĸ�32λ��ʱ��:0=t12��1=t34��2=t64
//����: ��
//-----------------------------------------------------------------------------
void Timer_Stop(u32 t64_no,u32 sub)
{
    tagTimerReg * timer;
    if(t64_no > 3)
        return;
    timer = __timer_get_timer_reg(t64_no);
    if(sub == 0)
        timer->TGCR &= ~(u32)1;
    else if(sub == 1)
        timer->TGCR &= ~(u32)2;
    else
        timer->TGCR &= ~(u32)3;
}

//----������ʱ��-------------------------------------------------------------
//����: ������ʱ��
//����: t64_no,�����õ�64λtimer��0~3
//      sub�������õ����ĸ�32λ��ʱ��:0=t12��1=t34��2=t64
//����: ��
//-----------------------------------------------------------------------------
void Timer_Start(u32 t64_no,u32 sub)
{
    tagTimerReg * timer;
    if(t64_no > 3)
        return;
    timer = __timer_get_timer_reg(t64_no);
    if(sub == 0)
        timer->TGCR |= 1;
    else if(sub == 1)
        timer->TGCR |= 2;
    else
        timer->TGCR |= 3;
}

//----�������ֵ---------------------------------------------------------------
//����: �����ʱ����ǰ����ֵ��
//����: t64_no,�����õ�64λtimer��0~3
//      sub������ĸ�32λ��ʱ��:0=t12��1=t34
//����: ��
//ע: ��ʱ���������޷��������ֵ��������ͣ�¡�
//-----------------------------------------------------------------------------
void timer_clear(u32 t64_no,u32 sub)
{
    tagTimerReg * timer;
    if(t64_no > 3)
        return;
    timer = __timer_get_timer_reg(t64_no);
    if(sub == 0)
        timer->TIM12 = 0;
    else if(sub == 1)
        timer->TIM34 = 0;
}

//----������ֵ---------------------------------------------------------------
//����: �����ʱ����ǰ����ֵ��
//����: t64_no,�����õ�64λtimer��0~3
//      sub�����ĸ�32λ��ʱ��:0=t12��1=t34
//����: ����ֵ
//-----------------------------------------------------------------------------
u32 Timer_Read(u32 t64_no,u32 sub)
{
    tagTimerReg * timer;
    if(t64_no > 3)
        return 0;
    timer = __timer_get_timer_reg(t64_no);
    if(sub == 0)
        return timer->TIM12;
    else
        return timer->TIM34;
}

