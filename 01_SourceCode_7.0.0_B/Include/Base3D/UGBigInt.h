
#if !defined(AFX_UGBIGINT_H__E89D0670_EB32_4782_8964_7F60F1421BCF__INCLUDED_)
#define AFX_UGBIGINT_H__E89D0670_EB32_4782_8964_7F60F1421BCF__INCLUDED_


#include <map>
#include "Stream/ugdefs.h"

namespace UGC
{
	class BASE3D_API UGBigInt
	{
	public:

		// ----------------
		// STATIC CONSTANTS
		// ----------------
		static const UGuint BIG_INT_MAJOR_VERSION = 4;
		static const UGuint BIG_INT_MINOR_VERSION = 0;

		static const UGuint DEC_DIGIT          = 10;
		static const UGuint HEX_DIGIT          = 16;
		static const UGuint NIBBLE_BIT         = 4;
		static const UGuint ULONG_HEX_DIGITS   = ((sizeof (UGulong) * CHAR_BIT)/NIBBLE_BIT);


		static const UGulong MAX_UNIT_VALUE   = (ULONG_MAX >> 2);
		static const UGulong ULONG_MSB        = static_cast<UGulong>(1) << (sizeof(UGulong) * CHAR_BIT - 1);

		static const UGulong BASE1        = 10;
		static const UGulong BASE2        = 1000000000;  // // BASE1 ** (BASE1 - 1)
		static const UGulong SUB_BASE2    = BASE2 - 1;  // 999999999
		static const UGulong OVER_BASE2   = 0xc0000000;  // OVER_BASE2 > SUB_BASE2

	protected:
		// --- Public Methods 
		UGArray<UGulong> m_units;
		static std::map<UGchar, UGuint> ms_hex2dec;

	public :
		// --- Public Methods ---


	private :
		// --- Private Methods ---
		void  ResizeUnits (UGuint i_size);
		void  TruncateUnits ();
		void  SmartTruncateUnits ();
		UGbool  BackUnitIsNull ();
		UGbool  InitViaString (const UGString& i_arg, UGuint i_digitBase);
		UGuint GetUnitsSize() const;

	public :
		// ----------------------
		// --- Public Methods ---
		// ----------------------
		// --- Constructors ---
		explicit UGBigInt ();
		~UGBigInt ();
		explicit UGBigInt (UGulong i_unit);
		explicit UGBigInt (const UGString& i_arg, UGuint i_digitBase);
		explicit UGBigInt (const UGuint i_noOfUnits, UGulong i_internalUnits, UGulong i_backUnit);

		UGbool  IsEmpty () const;

		static UGBigInt ModExp(UGBigInt m, UGBigInt e, UGBigInt n);

		// --- General purpose mathematical methods ---
		UGBigInt  operator+ (const UGBigInt& i_arg);
		UGBigInt  operator+ (UGulong i_arg);
		UGBigInt  operator* (UGBigInt i_arg);
		UGBigInt  operator* (UGulong i_arg);
		UGBigInt  operator/ (const UGBigInt& i_arg) const;
		UGBigInt  operator% (const UGBigInt& i_arg) const;
		UGBigInt  divide(const UGBigInt& i_dividend, const UGBigInt& i_divisor, UGBigInt* o_remainder) const;
		UGBigInt& operator+= (const UGBigInt& i_arg);
		UGBigInt  operator++ (UGint); // Post increment operator
		UGBigInt& operator++ ();    // Pre increment operator
		UGBigInt  operator-  (const UGBigInt& i_arg);
		UGBigInt  operator-  ();
		UGBigInt  operator-- (UGint); // Post decrement operator
		UGBigInt& operator-- ();    // Pre decrement operator
		UGBigInt& operator-= (const UGBigInt& i_arg);
		UGBigInt  sqrt();


		// --- Bitwise boolean operators ---
		UGBigInt  operator&   (const UGBigInt& i_arg);
		UGBigInt  operator|   (const UGBigInt& i_arg);
		UGBigInt  operator^   (const UGBigInt& i_arg);
		UGBigInt& operator&=  (const UGBigInt& i_arg);
		UGBigInt& operator|=  (const UGBigInt& i_arg);
		UGBigInt& operator^=  (const UGBigInt& i_arg);
		UGBigInt  operator~   ();
		UGBigInt  operator>>  (UGuint i_shift);
		UGBigInt  operator<<  (UGuint  i_shift);
		UGBigInt& operator>>= (UGuint  i_shift);
		UGBigInt& operator<<= (UGuint  i_shift);


		// --- Comparison operators ---
		UGbool operator== (const UGBigInt& i_arg) const;
		UGbool operator!= (const UGBigInt& i_arg) const;
		UGbool operator<  (const UGBigInt& i_arg) const;
		UGbool operator>  (const UGBigInt& i_arg) const;
		UGbool operator<= (const UGBigInt& i_arg) const;
		UGbool operator>= (const UGBigInt& i_arg) const;

		// --- Aux methods ---
		UGString ToStrHex (const UGString& i_prefix = _U(""));
		UGString ToStr0xHex ();
		UGString ToStrDec (const UGString& i_prefix = _U(""));	
		UGulong ToUlong ();

	};
}
#endif
