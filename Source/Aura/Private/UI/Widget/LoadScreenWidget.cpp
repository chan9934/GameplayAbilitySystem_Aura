// Copyright KimDongChan


#include "UI/Widget/LoadScreenWidget.h"

void ULoadScreenWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
