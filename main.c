#include "main.h"

// INT0割込
ISR(INT0_vect,ISR_BLOCK){
	// HIGNになるまで待つ
	while(DTR_IS_L) { __asm__ __volatile__ ("nop"); }
	count++;
}

// 結果表示
void result() {
	// 10回ならば、LED2を点灯する
	if(count==10) { LED2_L; }
	// 回数分LED1を点滅させる
	for(uint8_t i=0; i < count; i++ ) {
		LED1_L; _delay_ms(100); LED1_H; _delay_ms(250);
	}
	LED2_H;
}

// ループ処理
void loop() {
	// countを読むため割込禁止
	cli();
	// カウントされてないので割込を再開して戻る
	if(count == 0) { sei(); return; }
	// カウント中かもしれないので割込を再開し規定時間待つ
	sei();
	_delay_ms(SIGNAL_TIMEOUT);
	// タイムアウトしたので、割込禁止にして集計する
	cli();
	if(count>0) {
		result();
		count=0;
	}
}

int main(void) {
	// internal 8MHz
	CCP = 0xD8;
	CLKMSR = 0;

	// no prescale
	CCP = 0xD8;
	CLKPSR = 0;

	// ピン初期化
	LED1_OUT;
	LED2_OUT;
	DTR_IN;

	LED1_H;
	LED2_H;

	// カウンタ初期化
	count=0;

	// 割り込み
	cli();
	EIMSK = (1<<INT0);
	EICRA = 0;
	_delay_ms(500);
	sei();

    for(;;){
		loop();
	}
    return 0;
}

