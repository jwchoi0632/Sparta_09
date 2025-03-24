// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyIDPluginBPLibrary.h"
#include "MyIDPlugin.h"

FName UMyIDPluginBPLibrary::UserName = "";

UMyIDPluginBPLibrary::UMyIDPluginBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

void UMyIDPluginBPLibrary::SetUserName(const FName& NewName)
{
	UserName = NewName;
}

const FName& UMyIDPluginBPLibrary::GetUserName()
{
	return UserName;
}

