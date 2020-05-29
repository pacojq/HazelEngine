#include "hzpch.h"
#include "SubTexture2D.h"

namespace Hazel {

	SubTexture2D::SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max)
		: m_Texture(texture)
	{
		m_TexCoords[0] = { min.x, min.y };
		m_TexCoords[1] = { max.x, min.y };
		m_TexCoords[2] = { max.x, max.y };
		m_TexCoords[3] = { min.x, max.y };
	}


	Ref<SubTexture2D> SubTexture2D::CreateFromCoords(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& spriteSize,
		const glm::vec2& padding, const glm::vec2& offset)
	{
		glm::vec2 min = {
			(padding.x + coords.x * (spriteSize.x + offset.x)) / texture->GetWidth(),
			(padding.y + coords.y * (spriteSize.y + offset.y)) / texture->GetHeight()
		};
		
		glm::vec2 max = {
			(padding.x + (coords.x + 1) * (spriteSize.x + offset.x) - offset.x) / texture->GetWidth(),
			(padding.y + (coords.y + 1) * (spriteSize.y + offset.y) - offset.y) / texture->GetHeight()
		};

		return CreateRef<SubTexture2D>(texture, min, max);
	}

	
}