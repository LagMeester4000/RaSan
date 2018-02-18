#pragma once
#include "Types.h"

namespace rac
{
	class EntityId
	{
		friend class __EntityCreator;
	public:
		rac::u32 getIndex()
		{
			return (m_id & ~0xFF000000) | (0 & 0x00FFFFFF);
		}

		rac::u8 getVersion()
		{
			return m_id >> 24;
		}

		rac::u32 getRaw()
		{
			return m_id;
		}
	private:
		void setIndex(rac::u32 value)
		{
			m_id = (m_id & ~0x00FFFFFF) | (value & 0x00FFFFFF);
		}

		void setVersion(rac::u8 version)
		{
			m_id = (m_id & ~0xFF000000) | ((rac::u32)(version) << 24/* & 0xFF000000*/);
		}

	public:
		operator rac::u32()
		{
			return m_id;
		}
	private:
		rac::u32 m_id;

	public:
#ifdef RA_SERIALIZE
		//serialize
		template<typename Archive>
		void serialize(Archive &ar)
		{
			ar(m_id);
		}
#endif // RA_SERIALIZE
	};

	struct __EntityCreator
	{
		static EntityId createEntityId(rac::u32 index, rac::u8 version)
		{
			EntityId ret;
			ret.setIndex(index);
			ret.setVersion(version);
			return ret;
		}
	};
}