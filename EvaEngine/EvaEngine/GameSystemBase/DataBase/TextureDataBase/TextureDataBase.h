#pragma once

#include <vector>
#include "../../../Utility/Texture/Texture/Texture.h"

namespace EvaEngine {
	namespace Internal {
		class TextureDataBase {
		public:
			TextureDataBase() = default;
			~TextureDataBase() = default;

			

		private:
			std::vector<std::shared_ptr<Texture>> m_Textures;
		};
	}
}