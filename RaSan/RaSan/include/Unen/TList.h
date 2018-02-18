#pragma once

namespace unen
{
	struct void_t {};

	template<typename ... Types>
	struct TList {};

	template<typename ... First, typename ... Second>
	using AddTList = TList<First..., Second...>;

	template<typename ... First, typename ... Second>
	constexpr auto addTList(TList<First...>, TList<Second...>)
	{
		return TList<First..., Second...>{};
	}

	template<size_t ... S>
	struct SizeList {};

	template<size_t S, typename ... Types>
	constexpr size_t SizeOfTL_back = SizeOfTL_back<S, Types...>;
	template<size_t S, typename Front, typename ... Types>
	constexpr size_t SizeOfTL_back<S, Front, Types...> = SizeOfTL_back<S + 1, Types...>;
	template<size_t S, typename Last>
	constexpr size_t SizeOfTL_back<S, Last> = S;

	template<typename ... Types>
	constexpr size_t SizeOfTL = SizeOfTL_back<1, Types...>;

	template<size_t I, size_t Counter, typename ... Types>
	struct TypeAtIndex_back;
	template<size_t I, size_t Counter, typename First, typename ... Types>
	struct TypeAtIndex_back<I, Counter, First, Types...>
	{
		using type = typename TypeAtIndex_back<I, Counter + 1, Types...>::type;
	};
	template<size_t I, typename First, typename ... Types>
	struct TypeAtIndex_back<I, I, First, Types...>
	{
		using type = First;
	};

	template<size_t I, typename ... Types>
	using TypeAtIndex = typename TypeAtIndex_back<I, 0, Types...>::type;

	template<size_t I, typename ... Types>
	constexpr auto typeAtIndex(TList<Types...>)
	{
		return TypeAtIndex<I, Types...>{};
	}

	template<typename CompareType, typename First, typename ... Types>
	constexpr bool ContainsType = ContainsType<CompareType, Types...>;
	template<typename First, typename ... Types>
	constexpr bool ContainsType<First, First, Types...> = true;
	template<typename CompareType, typename First>
	constexpr bool ContainsType<CompareType, First> = false;

	template<typename CompareType, typename ... Types>
	constexpr bool containsType(TList<Types...>)
	{
		return ContainsType<CompareType, Types...>;
	}

	template<typename ... Types>
	struct IsEmpty_struct
	{
		constexpr static bool value = false;
	};
	template<>
	struct IsEmpty_struct<>
	{
		constexpr static bool value = true;
	};

	template<typename ... Types>
	constexpr bool IsEmpty = IsEmpty_struct<Types...>::value;

	template<typename ... Types>
	constexpr bool isEmpty(TList<Types...>)
	{
		return IsEmpty<Types...>;
	}
}