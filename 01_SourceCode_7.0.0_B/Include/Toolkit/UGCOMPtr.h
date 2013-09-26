//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file UGGraphics3DGL.h
//!  \brief OpenGL渲染系统
//!  \details 文件详细信息。
//!  \author malq
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Co., Ltd. <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace UGC 
{
	template<class T>
	class UGCOMPtr
	{
	public:
		UGCOMPtr():m_ptr(0)
		{

		}
		UGCOMPtr(const UGCOMPtr& ptr):m_ptr(ptr.m_ptr)
		{
			if(m_ptr)
			{
				m_ptr->AddRef();
			}
		}
		UGCOMPtr(T* ptr):m_ptr(ptr)
		{
			if(ptr)
			{
				m_ptr->AddRef();
			}
		}
		~UGCOMPtr()
		{
			if(m_ptr)
			{
				m_ptr->DecRef();
				m_ptr = 0;
			}
		}
	public:
		UGCOMPtr& operator = (const UGCOMPtr& ptr)
		{
			if(m_ptr == ptr.m_ptr)
			{
				return *this;
			}
			T* temp_ptr = m_ptr;
			m_ptr = ptr.m_ptr;
			if(m_ptr)
			{
				m_ptr->AddRef();
			}
			if(temp_ptr)
			{
				temp_ptr->DecRef();
			}
			return *this;
		}
		UGCOMPtr& operator = (T* ptr)
		{
			if(m_ptr == ptr)
			{
				return *this;
			}
			T* temp_ptr = m_ptr;
			m_ptr = ptr;
			if(m_ptr)
			{
				m_ptr->AddRef();
			}
			if(temp_ptr)
			{
				temp_ptr->DecRef();
			}
			return *this;
		}
		UGbool   operator == (const UGCOMPtr& ptr) const
		{
			return m_ptr == ptr.m_ptr;
		}
		UGbool   operator == (const T* ptr) const
		{
			return m_ptr == ptr;
		}
		UGbool   operator != (const UGCOMPtr& ptr) const 
		{
			return m_ptr != ptr.m_ptr;
		}
		UGbool   operator != (const T* ptr) const 
		{
			return m_ptr != ptr;
		}

		UGbool operator < (const UGCOMPtr& ptr) const 
		{ 
			return (m_ptr<ptr.m_ptr); 
		}

		UGbool operator < (const T& ptr) const 
		{ 
			return (m_ptr<ptr); 
		}

		UGbool operator > (const UGCOMPtr& ptr) const 
		{ 
			return (m_ptr>ptr.m_ptr); 
		}

		UGbool operator > (const T& ptr) const 
		{ 
			return (m_ptr>ptr); 
		}

		T*       operator -> () const
		{
			return m_ptr;
		}
		T&       operator * () const
		{
			return *m_ptr;
		}

		UGbool   operator ! () const 
		{
			return m_ptr == NULL;
		}

		T*       Get() const
		{
			return m_ptr;
		}

		UGbool Valid()
		{
			return m_ptr != NULL;
		}
	private:
		T* m_ptr;
	};
}

