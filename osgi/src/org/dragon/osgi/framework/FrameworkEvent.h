#include "osgi_framework.h"

#ifndef OSGI_Framework_FrameworkEvent_H 
#define OSGI_Framework_FrameworkEvent_H 
#pragma once

BeginPackageOSGIFramework

interface _DragonExport FrameworkEvent
{
public:
	enum TYPE
	{
    STARTED=0x00000001,

    /**
     * An error has occurred.
     * <p>
     * There was an error associated with a bundle.
     * <p>
     * The value of <code>ERROR</code> is 0x00000002.
     */
    _ERROR=0x00000002,

    /**
     * A StartLevel.setStartLevel operation has completed.
     * <p>
     * This event is fired when the Framework has completed changing the active start level initiated by a call to the
     * StartLevel.setStartLevel method.
     * <p>
     * The value of <code>STARTLEVEL_CHANGED</code> is 0x00000008.
     */
    STARTLEVEL_CHANGED=0x00000008,

    /**
     * A warning has occurred.
     * <p>
     * There was a warning associated with a bundle.
     * <p>
     * The value of <code>WARNING</code> is 0x00000010.
     */
    WARNING=0x00000010,

    /**
     * An informational event has occurred.
     * <p>
     * There was an informational event associated with a bundle.
     * <p>
     * The value of <code>INFO</code> is 0x00000020.
     */
    INFO=0x00000020,

    /**
     * An debug event has occurred.
     * <p>
     * There was an debug event associated with a bundle or framework.
     * <p>
     * The value of <code>DEBUG</code> is 0x00000030.
     */
    DEBUG=0x00000030,

    /**
     * A framework stop event has occurred.
     * <p>
     * This event is fired when the Framework has shutdown after all bundles uninstalled.
     * <p>
     * The value of <code>STOPPED</code> is 0xFFFFFFFF.
     */
    STOPPED=0xFFFFFFFF
  };

public:
	virtual ~FrameworkEvent(){};

	  /**
   * Returns the type of framework event.
   * <p>
   * The type values are:
   * <ul>
   * <li>{@link TYPE#STARTED}
   * <li>{@link TYPE#ERROR}
   * <li>{@link TYPE#WARNING}
   * <li>{@link TYPE#INFO}
   * </ul>
   * 
   * @return The type of state change.
   */
  virtual TYPE getType()=0;

  /**
   * Returns the message related to this event.
   * 
   * @return The related message or <code>null</code> if none.
   */
  virtual String getMessage()=0;

  /**
   * Returns the exception related to this event.
   * 
   * @return The related exception or <code>null</code> if none.
   */
  virtual P<Throwable> getThrowable()=0;

  /**
   * Returns the bundle associated with the event. This bundle is also the source of the event.
   * 
   * @return The bundle associated with the event.
   */
  virtual P<Bundle> getBundle()=0;

};

EndPackageOSGIFramework

#endif