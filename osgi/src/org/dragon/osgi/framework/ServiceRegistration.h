/*
 * Copyright (c) www.yubing.org (2009, 2020). All Rights Reserved.
 *
 * Name : yubing
 * Email: yubing744@163.com
 * QQ   : 812985117
 *
 */

#include "osgi_framework.h"

#ifndef OSGI_Framework_ServiceRegistration_H 
#define OSGI_Framework_ServiceRegistration_H 
#pragma once

BeginPackageOSGIFramework

/**
 * A registered service.
 * 
 * <p>
 * The Framework returns a <code>ServiceRegistration</code> object when a
 * <code>BundleContext.registerService</code> method invocation is successful.
 * The <code>ServiceRegistration</code> object is for the private use of the
 * registering bundle and should not be shared with other bundles.
 * <p>
 * The <code>ServiceRegistration</code> object may be used to update the
 * properties of the service or to unregister the service.
 * 
 * @see BundleContext#registerService(String[],Object,Dictionary)
 * @ThreadSafe
 * @version $Revision: 6361 $
 */

interface _DragonExport ServiceRegistration
{
public:
	virtual ~ServiceRegistration(){};

public:
	/**
	 * Returns a <code>ServiceReference</code> object for a service being
	 * registered.
	 * <p>
	 * The <code>ServiceReference</code> object may be shared with other
	 * bundles.
	 * 
	 * @throws IllegalStateException If this
	 *         <code>ServiceRegistration</code> object has already been
	 *         unregistered.
	 * @return <code>ServiceReference</code> object.
	 */
	virtual P<ServiceReference> getReference()=0;

	/**
	 * Updates the properties associated with a service.
	 * 
	 * <p>
	 * The {@link Constants#OBJECTCLASS} and {@link Constants#SERVICE_ID} keys
	 * cannot be modified by this method. These values are set by the Framework
	 * when the service is registered in the OSGi environment.
	 * 
	 * <p>
	 * The following steps are required to modify service properties:
	 * <ol>
	 * <li>The service's properties are replaced with the provided properties.
	 * <li>A service event of type {@link ServiceEvent#MODIFIED} is fired.
	 * </ol>
	 * 
	 * @param properties The properties for this service. See {@link Constants}
	 *        for a list of standard service property keys. Changes should not
	 *        be made to this object after calling this method. To update the
	 *        service's properties this method should be called again.
	 * 
	 * @throws IllegalStateException If this <code>ServiceRegistration</code>
	 *         object has already been unregistered.
	 * @throws IllegalArgumentException If <code>properties</code> contains
	 *         case variants of the same key name.
	 */
	virtual void setProperties(P<Map<String,String>> properties)=0;

	/**
	 * Unregisters a service. Remove a <code>ServiceRegistration</code> object
	 * from the Framework service registry. All <code>ServiceReference</code>
	 * objects associated with this <code>ServiceRegistration</code> object
	 * can no longer be used to interact with the service once unregistration is
	 * complete.
	 * 
	 * <p>
	 * The following steps are required to unregister a service:
	 * <ol>
	 * <li>The service is removed from the Framework service registry so that
	 * it can no longer be obtained.
	 * <li>A service event of type {@link ServiceEvent#UNREGISTERING} is fired
	 * so that bundles using this service can release their use of the service.
	 * Once delivery of the service event is complete, the
	 * <code>ServiceReference</code> objects for the service may no longer be
	 * used to get a service object for the service.
	 * <li>For each bundle whose use count for this service is greater than
	 * zero: <br>
	 * The bundle's use count for this service is set to zero. <br>
	 * If the service was registered with a {@link ServiceFactory} object, the
	 * <code>ServiceFactory.ungetService</code> method is called to release
	 * the service object for the bundle.
	 * </ol>
	 * 
	 * @throws IllegalStateException If this
	 *         <code>ServiceRegistration</code> object has already been
	 *         unregistered.
	 * @see BundleContext#ungetService
	 * @see ServiceFactory#ungetService
	 */
	virtual void unregister()=0;

	virtual P<Object> getService(P<BundleContext> user)=0;
	virtual bool ungetService(P<BundleContext> user)=0;
	virtual	P<Array<String>> getClasses()=0;

};

EndPackageOSGIFramework

#endif