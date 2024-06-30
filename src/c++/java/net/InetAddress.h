/*******************************************************************************
*  JNOC++ - Java Network Object Comminication ++:
*	is the implementation of Java Object Serialization protocol
*
*  Copyright (C) 1997 - 2002 iNexum Systems Inc.
*  This library is free software; you can redistribute it and/or
*  modify it under the terms of the GNU Lesser General Public
*  License as published by the Free Software Foundation; either
*  version 2.1 of the License, or (at your option) any later version.
*  
*  This library is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
*  Lesser General Public License for more details.
*  
*  You should have received a copy of the GNU Lesser General Public
*  License along with this library; if not, write to the Free Software
*  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
*  Using the Lesser GPL permits use of the library in proprietary programs; 
*  Using the ordinary GPL for a library makes it available only for free 
*  programs.
*******************************************************************************/
/*----------------------------------------------------------------------------*
 *                                                                            *
 * File:		InetAddress.h
 * Description:	
 * Notes:
 *
 * Modification History:	YYMMDD	Author		Description
 * ------ ---- --- -----------------------------------------------------------*
 					030303	nmv			create
 *----------------------------------------------------------------------------*/

#ifndef java_net_InetAddress_h
#define java_net_InetAddress_h

#ifdef _WINDOWS
        #include <winsock2.h>
#else
        #include <sys/socket.h>
#endif
#include <string>
#include <vector>
#include <java/lang/Exception.h>

/** iNexum's java classes implemented in C++.
  *
  * @author		iNexum Systems Inc.
  * @version	1.0.0
  */
namespace java
{
	/** iNexum's java/net classes implemented in C++.
	  *
	  * @author		iNexum Systems Inc.
	  * @version	1.0.0
	  */
	namespace net
	{
		class UnknownHostException : public java::lang::Exception {};

		/** This class represents an Internet Protocol (IP) address.
		  *
		  * @memo NOT SUPPOTED by this version.
		  *
		  * @author		iNexum Systems Inc.
		  * @version	1.0.0
		  */
		class InetAddress
		{
		public:
			/** Utility routine to check if the InetAddress is an IP multicast address.
			  *	Returns:
			  *	a bool indicating if the InetAddress is an IP multicast address
			  */
			 bool isMulticastAddress() const;

			/** Utility routine to check if the InetAddress in a wildcard address. 
			  *	Returns:
			  *	a bool indicating if the Inetaddress is a wildcard address.
			  */
			 bool isAnyLocalAddress() const;

			/** Utility routine to check if the InetAddress is a loopback address. 
			  *	Returns:
			  *	a bool indicating if the InetAddress is a loopback address; or 
			  * false otherwise.
			  */
			 bool isLoopbackAddress() const;

			/** Utility routine to check if the InetAddress is an link local address. 
			  *	Returns:
			  *	a bool indicating if the InetAddress is a link local address; or 
			  * false if address is not a link local unicast address.
			  */
			 bool isLinkLocalAddress() const;

			/** Utility routine to check if the InetAddress is a site local address. 
			  *	Returns:
			  *	a bool indicating if the InetAddress is a site local address; or 
			  *	false if address is not a site local unicast address.
			  */
			 bool isSiteLocalAddress() const;

			/** Utility routine to check if the multicast address has global scope.
			  *	Returns:
			  *	a bool indicating if the address has is a multicast address of 
			  * global scope, false if it is not of global scope or it is not a 
			  * multicast address
			  */
			 bool isMCGlobal() const;

			/** Utility routine to check if the multicast address has node scope. 
			  *	Returns:
			  *	a bool indicating if the address has is a multicast address of 
			  * node-local scope, false if it is not of node-local scope or it is 
			  * not a multicast address
			  */
			 bool isMCNodeLocal() const;

			/** Utility routine to check if the multicast address has link scope.
			  *	Returns:
			  *	a bool indicating if the address has is a multicast address of 
			  * link-local scope, false if it is not of link-local scope or it is 
			  * not a multicast address
			  */
			 bool isMCLinkLocal() const;

			/** Utility routine to check if the multicast address has site scope.
			  *	Returns:
			  *	a bool indicating if the address has is a multicast address of 
			  * site-local scope, false if it is not of site-local scope or it is 
			  * not a multicast address
			  */
			 bool isMCSiteLocal() const;

			/** Utility routine to check if the multicast address has organization 
			  * scope. 
			  *	Returns:
			  *	a bool indicating if the address has is a multicast address of 
			  * organization-local scope, false if it is not of organization-local 
			  * scope or it is not a multicast address
			  */
			 bool isMCOrgLocal() const;

			/** Gets the host name for this IP address. 
			  *	If this InetAddress was created with a host name, this host name will
			  * be remembered and returned; otherwise, a reverse name lookup will be 
			  * performed and the result will be returned based on the system 
			  * configured name lookup service. If a lookup of the name service is 
			  * required, call getCanonicalHostName. 
			  *	If there is a security manager, its checkConnect method is first called 
			  * with the hostname and -1 as its arguments to see if the operation is 
			  * allowed. If the operation is not allowed, it will return the textual 
			  * representation of the IP address. 
			  *	Returns:
			  *	the host name for this IP address, or if the operation is not allowed by
			  * the security check, the textual representation of the IP address.
			  *	See Also:
			  *	getCanonicalHostName(), SecurityManager.checkConnect(java.lang.const std::string&, int)
			  */
			 std::string getHostName() const;

			/** Gets the fully qualified domain name for this IP address. Best effort 
			  * method, meaning we may not be able to return the FQDN depending on the 
			  * underlying system configuration. 
			  *	If there is a security manager, this method first calls its 
			  * checkConnect method with the hostname and -1 as its arguments to see 
			  * if the calling code is allowed to know the hostname for this IP address,
			  * i.e., to connect to the host. If the operation is not allowed, it will
			  * return the textual representation of the IP address. 
			  *	Returns:
			  *	the fully qualified domain name for this IP address, or if the operation 
			  * is not allowed by the security check, the textual representation of the 
			  * IP address.
			  *	See Also:
			  *	SecurityManager.checkConnect(java.lang.std::string, int)
			  */
			 std::string getCanonicalHostName() const;

			/** Returns the raw IP address of this InetAddress object. The result is in 
			  * network byte order: the highest order byte of the address is in 
			  * getAddress()[0]. 
			  *	Returns:
			  *	the raw IP address of this object.
			  */
			 byte* getAddress() const;


			/** Returns the IP address std::string in textual presentation. 
			  *	Returns:
			  *	the raw IP address in a std::string format.
			  */
			 std::string getHostAddress() const;

			/** Returns a hashcode for this IP address. 
			  *	Overrides:
			  *	hashCode in class Object
			  *	Returns:
			  *	a hash code value for this IP address.
			  *	See Also:
			  *	Object.equals(java.lang.Object), Hashtable
			  */
			 int hashCode() const;


			/** Compares this object against the specified object. The result is true if
			  * and only if the argument is not null and it represents the same IP 
			  * address as this object. 
			  *	Two instances of InetAddress represent the same IP address if the length
			  * of the byte arrays returned by getAddress is the same for both, and each
			  * of the array components is the same for the byte arrays. 
			  *	Overrides:
			  *	equals in class Object
			  *	Parameters:
			  *	obj - the object to compare against. 
			  *	Returns:
			  *	true if the objects are the same; false otherwise.
			  *	See Also:
			  *	getAddress()
			  */
			 bool equals(const void* obj) const;

			 bool operator==(const InetAddress& right) const;

			/** Converts this IP address to a std::string. The std::string returned is of the form: hostname / literal IP address. If the host name is unresolved, no reverse name service loopup is performed. The hostname part will be represented by an empty std::string. 
			  *	Overrides:
			  *	tostd::string in class Object
			  *	Returns:
			  *	a std::string representation of this IP address.
			  */
			 std::string toString() const;

			 operator std::string() const;


			/** Create an InetAddress based on the provided host name and IP address No 
			  * name service is checked for the validity of the address. 
			  *	The host name can either be a machine name, such as "java.sun.com", or 
			  * a textual representation of its IP address. 

			  *	For host specified in literal IPv6 address, either the form defined in 
			  * RFC 2732 or the literal IPv6 address format defined in RFC 2373 is 
			  * accepted. 

			  *	If addr specifies an IPv4 address an instance of Inet4Address will be 
			  * returned; otherwise, an instance of Inet6Address will be returned. 

			  *	IPv4 address byte array must be 4 bytes long and IPv6 byte array must 
			  * be 16 bytes long
			  *	Parameters:
			  *	host - the specified host
			  *	addr - the raw IP address in network byte order 
			  *	Returns:
			  *	an InetAddress object created from the raw IP address. 
			  *	Throws: 
			  *	UnknownHostException* - if IP address is of illegal length
			  */
			 static InetAddress getByAddress(const std::string& host, byte* addr)
													throw(UnknownHostException*);


			/** Determines the IP address of a host, given the host's name. 
			  *	The host name can either be a machine name, such as "java.sun.com", 
			  * or a textual representation of its IP address. If a literal IP 
			  * address is supplied, only the validity of the address format is checked. 
			  *	For host specified in literal IPv6 address, either the form defined in 
			  * RFC 2732 or the literal IPv6 address format defined in RFC 2373 is 
			  * accepted. 
			  *	If the host is null then an InetAddress representing an address of 
			  * the loopback interface is returned. See RFC 3330 section 2 and RFC 
			  * 2373 section 2.5.3. 
			  *	Parameters:
			  *	host - the specified host, or null. 
			  *	Returns:
			  *	an IP address for the given host name. 
			  *	Throws: 
			  *	UnknownHostException* - if no IP address for the host could be found. 
			  *	SecurityException - if a security manager exists and its checkConnect
			  * method doesn't allow the operation
			  */
			static InetAddress getByName(const std::string& host)
												throw(UnknownHostException*);

			/** Given the name of a host, returns an array of its IP addresses, based
			  * on the configured name service on the system. 
			  *	The host name can either be a machine name, such as "java.sun.com", 
			  * or a textual representation of its IP address. If a literal IP address
			  * is supplied, only the validity of the address format is checked. 
			  *	For host specified in literal IPv6 address, either the form defined in 
			  * RFC 2732 or the literal IPv6 address format defined in RFC 2373 is 
			  * accepted. 
			  *	If the host is null then an InetAddress representing an address of the
			  * loopback interface is returned. See RFC 3330 section 2 and RFC 2373 
			  * section 2.5.3. 
			  *	If there is a security manager and host is not null and host.length()
			  * is not equal to zero, the security manager's checkConnect method is 
			  * called with the hostname and -1 as its arguments to see if the 
			  * operation is allowed. 
			  *	Parameters:
			  *	host - the name of the host, or null. 
			  *	Returns:
			  *	an array of all the IP addresses for a given host name. 
			  *	Throws: 
			  *	UnknownHostException* - if no IP address for the host could be found. 
			  *	SecurityException - if a security manager exists and its checkConnect
			  * method doesn't allow the operation.
			  *	See Also:
			  *	SecurityManager.checkConnect(java.lang.std::string, int)
			  */
			static std::vector<InetAddress> getAllByName(const std::string& host)
													throw(UnknownHostException*);

			/** Returns an InetAddress object given the raw IP address. The argument 
			  * is in network byte order: the highest order byte of the address is 
			  * in getAddress()[0]. 
			  *	This method doesn't block, i.e. no reverse name service lookup is 
			  * performed. 
			  *	IPv4 address byte array must be 4 bytes long and IPv6 byte array must
			  * be 16 bytes long 
			  *	Parameters:
			  *	addr - the raw IP address in network byte order 
			  *	Returns:
			  *	an InetAddress object created from the raw IP address. 
			  *	Throws: 
			  *	UnknownHostException* - if IP address is of illegal length
			  */
			static InetAddress getByAddress(byte* addr)
											throw(UnknownHostException*);

			/** Returns the local host.
			  *	If there is a security manager, its checkConnect method is called 
			  * with the local host name and -1 as its arguments to see if the 
			  * operation is allowed. If the operation is not allowed, an 
			  * InetAddress representing the loopback address is returned. 
			  *	Returns:
			  *	the IP address of the local host. 
			  *	Throws: 
			  *	UnknownHostException* - if no IP address for the host could be found.
			  *	See Also:
			  *	SecurityManager.checkConnect(java.lang.std::string, int)
			  */
			static InetAddress getLocalHost() throw(UnknownHostException*);

		protected:
			InetAddress(unsigned long address) : mAddress(address) {};

			InetAddress(const std::string& host, byte* address) : mHostName(host) {};

		private:
			unsigned long	mAddress;
			std::string		mHostName;
		};
	}	// namespace net
} // namespace java

#endif	// java_net_InetAddress_h