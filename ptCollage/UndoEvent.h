#include <pxStdDef.h>

///////////////////////////////////////////////
// 以下の時にアンドゥはクリアされる
// ・プロジェクトが初期化されたりロードされた時
// ・ユニットが削除された時
///////////////////////////////////////////////

bool UndoEvent_Initialize( int32_t  max_unit );
// 開放
void UndoEvent_ReleaseUndoRedo();
void UndoEvent_ReleaseRedo(     void );
void UndoEvent_Release(         void );

void UndoEvent_SetOrderUnit( int32_t  u );
void UndoEvent_SetOrderClock( int32_t  clock1, int32_t  clock2 );
bool UndoEvent_Push( bool bUndo );

// アンドゥ１回取り消し
void UndoEvent_Back();

// アンドゥポップ
bool UndoEvent_Pop( bool bUndo );

// 待機アンドゥはあるか？
bool UndoEvent_IsUndoZero(   void );
bool UndoEvent_IsRedoZero(   void );

// アンドゥ位置
int32_t  UndoEvent_GetUndoIndex();
int32_t  UndoEvent_GetRedoIndex();

void UndoEvent_Replace_UnitNo(  int32_t  old_pos, int32_t  new_pos );
void UndoEvent_Replace_VoiceNo( int32_t  old_pos, int32_t  new_pos );
