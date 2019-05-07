//==============================================================================
//
//  OvenMediaEngine
//
//  Created by Hyunjun Jang
//  Copyright (c) 2018 AirenSoft. All rights reserved.
//
//==============================================================================
#pragma once

#include "../item.h"

namespace cfg
{
	struct Origin : public Item
	{
		int GetListenPort() const
		{
			return _listen_port;
		}

		ov::String GetPrimary() const
		{
			return _primary;
		}

		ov::String GetSecondary() const
		{
			return _secondary;
		}

		ov::String GetAlias() const
		{
			return _alias;
		}

	protected:
		void MakeParseList() const override
		{
			RegisterValue<Optional>("ListenPort", &_listen_port);
			RegisterValue<Optional>("Primary", &_primary);
			RegisterValue<Optional>("Secondary", &_secondary);
			RegisterValue<Optional>("Alias", &_alias);
		}

		int _listen_port = 9000;
		ov::String _primary;
		ov::String _secondary;
		ov::String _alias;
	};
}