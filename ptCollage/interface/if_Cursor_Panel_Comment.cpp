
#include "../../Generic/KeyControl.h"

#include "if_Panel_Comment.h"

// 音符編集カーソル
bool if_Cursor_Action_Panel_Comment( float cur_x, float cur_y )
{
	if( !KeyControl_IsClickLeftTrigger() ) return false;
	return if_Panel_Comment_HitButton( cur_x, cur_y );
}
