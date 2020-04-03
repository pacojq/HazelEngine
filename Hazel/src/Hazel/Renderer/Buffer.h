#pragma once

/*
	A vertex buffer is used to store the vertices of a mesh.
	They can be ordered using a given BufferLayout.

	For example, a "hello-world" triangle would be like:


			float vertices[3 * 7] = {
				-0.5f, -0.5f, 0.0f,		0.8f, 0.0f, 0.2f, 1.0f,     // First vertex
				0.5f, -0.5f, 0.0f,		0.2f, 0.3f, 0.8f, 1.0f,     // Second vertex
				0.0f,  0.5f, 0.0f,		0.8f, 0.8f, 0.2f, 1.0f,     // Third vertex
			};

			Ref<Hazel::VertexBuffer> vertexBuffer;
			vertexBuffer.reset(Hazel::VertexBuffer::Create(vertices, sizeof(vertices)));

			Hazel::BufferLayout layout = {
				{ Hazel::ShaderDataType::Float3, "a_Position" },
				{ Hazel::ShaderDataType::Float4, "a_Color" }
			};
			vertexBuffer->SetLayout(layout);


	We define a layout in which, for each vertex, we have a Float3 indicating
	its position and a Float4 storing its color.

	After having the vertices ready, we can go and set up the incides in the IndexBuffer:


			uint32_t indices[3] = { 0, 1, 2 };
			Ref<Hazel::IndexBuffer> indexBuffer;
			indexBuffer.reset(Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));


	And finally we can put them both together inside the VertexArray:

			m_VertexArray.reset(Hazel::VertexArray::Create());
			m_VertexArray->AddVertexBuffer(vertexBuffer);
			m_VertexArray->SetIndexBuffer(indexBuffer);
*/
namespace Hazel {




	enum class ShaderDataType
	{
		None = 0,
		Float, Float2, Float3, Float4,
		Mat3, Mat4,
		Int, Int2, Int3, Int4,
		Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:		return 4;
			case ShaderDataType::Float2:	return 4 * 2;
			case ShaderDataType::Float3:	return 4 * 3;
			case ShaderDataType::Float4:	return 4 * 4;


			case ShaderDataType::Mat3:		return 4 * 3 * 3;
			case ShaderDataType::Mat4:		return 4 * 4 * 4;

			case ShaderDataType::Int:		return 4;
			case ShaderDataType::Int2:		return 4 * 2;
			case ShaderDataType::Int3:		return 4 * 3;
			case ShaderDataType::Int4:		return 4 * 4;

			case ShaderDataType::Bool:		return 1;
		}

		HZ_CORE_ASSERT(false, "Unknown ShaderDataType");
		return 0;
	}

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;

		BufferElement() {}

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{			
		}

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
			case ShaderDataType::Float:		return 1;
			case ShaderDataType::Float2:	return 2;
			case ShaderDataType::Float3:	return 3;
			case ShaderDataType::Float4:	return 4;


			case ShaderDataType::Mat3:		return 3 * 3;
			case ShaderDataType::Mat4:		return 4 * 4;

			case ShaderDataType::Int:		return 1;
			case ShaderDataType::Int2:		return 2;
			case ShaderDataType::Int3:		return 3;
			case ShaderDataType::Int4:		return 4;

			case ShaderDataType::Bool:		return 1;
			}

			HZ_CORE_ASSERT(false, "Unknown ShaderDataType");
			return 0;
		}
	};




	/*
		Determines how the data inside the VertexBuffer is structured.
		For each vertex, we will have one or many BufferElements.
	*/
	class BufferLayout
	{
	public:

		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement> elements)
			: m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		inline uint32_t GetStride() const { return m_Stride; }
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

	private:
		void CalculateOffsetsAndStride()
		{
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}

	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride;
	};





	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		virtual void SetData(const void* data, uint32_t size) = 0;

		static Ref<VertexBuffer> Create(uint32_t size);
		static Ref<VertexBuffer> Create(float* vertices, uint32_t size);
	};





	// Currently Hazel only supports 32-bit index buffers
	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t count);
	};

}