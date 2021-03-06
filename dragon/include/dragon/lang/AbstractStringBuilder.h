/*
* Copyright 2013 the original author or authors.
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*      http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

/**********************************************************************
 * Author:      Owen Wu/wcw/yubing
 * Email:       yubing744@163.com
 * Created:     2013/03/31
 **********************************************************************/


#ifndef AbstractStringBuilder_Lang_Dragon_H
#define AbstractStringBuilder_Lang_Dragon_H

#include <dragon/config.h>

#include <dragon/lang/Array.h>
#include <dragon/lang/String.h>
#include <dragon/lang/Object.h>

BeginPackage2(dragon, lang)

Import dragon::lang;

/**
 * A mutable sequence of wchar_uacters.
 * <p>
 * Implements a modifiable string. At any point in time it contains some 
 * particular sequence of wchar_uacters, but the length and content of the 
 * sequence can be changed through certain method calls.
 */
class_ AbstractStringBuilder 
    extends(Object) {
public:

    /** 
     * This no-arg constructor is necessary for serialization of subclasses.
     */
	AbstractStringBuilder();

    /** 
     * Creates an AbstractStringBuilder of the specified capacity.
     */
	AbstractStringBuilder(int capcity);

    /** 
     * This deconstructor.
     */
	virtual ~AbstractStringBuilder();

public:
	/**
     * Returns the length (character count).
     *
     * @return  the length of the sequence of characters currently 
     *          represented by this object
     */
	virtual int length();


    /**
     * Returns the current capacity. The capacity is the amount of storage 
     * available for newly inserted characters, beyond which an allocation 
     * will occur.
     *
     * @return  the current capacity
     */	
	virtual int capcity();

    /**
     * Ensures that the capacity is at least equal to the specified minimum.
     * If the current capacity is less than the argument, then a new internal
     * array is allocated with greater capacity. The new capacity is the 
     * larger of: 
     * <ul>
     * <li>The <code>minimumCapacity</code> argument. 
     * <li>Twice the old capacity, plus <code>2</code>. 
     * </ul>
     * If the <code>minimumCapacity</code> argument is nonpositive, this
     * method takes no action and simply returns.
     *
     * @param   minimumCapacity   the minimum desired capacity.
     */
	virtual void ensureCapacity(int minimumCapacity);

	/**
     * Attempts to reduce storage used for the character sequence.
     * If the buffer is larger than necessary to hold its current sequence of 
     * characters, then it may be resized to become more space efficient. 
     * Calling this method may, but is not required to, affect the value 
     * returned by a subsequent call to the {@link #capacity()} method.
     */
    virtual void trimToSize();

    /**
     * Sets the length of the character sequence.
     * The sequence is changed to a new character sequence 
     * whose length is specified by the argument. For every nonnegative 
     * index <i>k</i> less than <code>newLength</code>, the wchar_uacter at 
     * index <i>k</i> in the new wchar_uacter sequence is the same as the 
     * character at index <i>k</i> in the old sequence if <i>k</i> is less 
     * than the length of the old wchar_uacter sequence; otherwise, it is the 
     * null wchar_uacter <code>'&#92;u0000'</code>. 
     *  
     * In other words, if the <code>newLength</code> argument is less than 
     * the current length, the length is changed to the specified length.
     * <p>
     * If the <code>newLength</code> argument is greater than or equal 
     * to the current length, sufficient null wchar_uacters 
     * (<code>'&#92;u0000'</code>) are appended so that 
     * length becomes the <code>newLength</code> argument. 
     * <p>
     * The <code>newLength</code> argument must be greater than or equal 
     * to <code>0</code>. 
     *
     * @param      newLength   the new length
     * @throws     IndexOutOfBoundsException  if the
     *               <code>newLength</code> argument is negative.
     */
    virtual void setLength(int newLength);

   /**
     * Returns the <code>wchar_u</code> value in this sequence at the specified index.
     * The first <code>wchar_u</code> value is at index <code>0</code>, the next at index
     * <code>1</code>, and so on, as in array indexing.
     * <p>
     * The index argument must be greater than or equal to
     * <code>0</code>, and less than the length of this sequence.
     *
     * <p>If the <code>wchar_u</code> value specified by the index is a
     * <a href="Character.html#unicode">surrogate</a>, the surrogate
     * value is returned.
     *
     * @param      index   the index of the desired <code>wchar_u</code> value.
     * @return     the <code>wchar_u</code> value at the specified index.
     * @throws     IndexOutOfBoundsException  if <code>index</code> is 
     *             negative or greater than or equal to <code>length()</code>.
     */
    virtual wchar_u charAt(int index);

    /**
     * Characters are copied from this sequence into the 
     * destination wchar_uacter array <code>dst</code>. The first wchar_uacter to 
     * be copied is at index <code>srcBegin</code>; the last wchar_uacter to 
     * be copied is at index <code>srcEnd-1</code>. The total number of 
     * wchar_uacters to be copied is <code>srcEnd-srcBegin</code>. The 
     * wchar_uacters are copied into the subarray of <code>dst</code> starting 
     * at index <code>dstBegin</code> and ending at index:
     * <p><blockquote><pre>
     * dstbegin + (srcEnd-srcBegin) - 1
     * </pre></blockquote>
     *
     * @param      srcBegin   start copying at this offset.
     * @param      srcEnd     stop copying at this offset.
     * @param      dst        the array to copy the data into.
     * @param      dstBegin   offset into <code>dst</code>.
     * @throws     NullPointerException if <code>dst</code> is 
     *             <code>null</code>.
     * @throws     IndexOutOfBoundsException  if any of the following is dg_true:
     *             <ul>
     *             <li><code>srcBegin</code> is negative
     *             <li><code>dstBegin</code> is negative
     *             <li>the <code>srcBegin</code> argument is greater than 
     *             the <code>srcEnd</code> argument.
     *             <li><code>srcEnd</code> is greater than 
     *             <code>this.length()</code>.
     *             <li><code>dstBegin+srcEnd-srcBegin</code> is greater than 
     *             <code>dst.length</code>
     *             </ul>
     */
    virtual void getChars(int srcBegin, int srcEnd, wchar_u* dst, int dstBegin);  

	/**
     * The character at the specified index is set to <code>ch</code>. This 
     * sequence is altered to represent a new character sequence that is 
     * identical to the old character sequence, except that it contains the 
     * wchar_uacter <code>ch</code> at position <code>index</code>. 
     * <p>
     * The index argument must be greater than or equal to 
     * <code>0</code>, and less than the length of this sequence. 
     *
     * @param      index   the index of the character to modify.
     * @param      ch      the new character.
     * @throws     IndexOutOfBoundsException  if <code>index</code> is 
     *             negative or greater than or equal to <code>length()</code>.
     */
    virtual void setCharAt(int index, wchar_u ch) ;

    /**
     * Appends the specified string to this wchar_uacter sequence.
     * <p>
     * The wchar_uacters of the <code>String</code> argument are appended, in 
     * order, increasing the length of this sequence by the length of the 
     * argument. If <code>str</code> is <code>null</code>, then the four 
     * wchar_uacters <code>"null"</code> are appended.
     * <p>
     * Let <i>n</i> be the length of this wchar_uacter sequence just prior to 
     * execution of the <code>append</code> method. Then the wchar_uacter at 
     * index <i>k</i> in the new wchar_uacter sequence is equal to the wchar_uacter 
     * at index <i>k</i> in the old wchar_uacter sequence, if <i>k</i> is less 
     * than <i>n</i>; otherwise, it is equal to the wchar_uacter at index 
     * <i>k-n</i> in the argument <code>str</code>.
     *
     * @param   str   a string.
     * @return  a reference to this object.
     */
    virtual AbstractStringBuilder* append(String* str);
    virtual AbstractStringBuilder* append(const String& str);
    virtual AbstractStringBuilder* append(CharSequence* seq);

    /**
     * Appends a subsequence of the specified <code>CharSequence</code> to this
     * sequence.
     * <p>
     * Characters of the argument <code>s</code>, starting at
     * index <code>start</code>, are appended, in order, to the contents of
     * this sequence up to the (exclusive) index <code>end</code>. The length
     * of this sequence is increased by the value of <code>end - start</code>.
     * <p>
     * Let <i>n</i> be the length of this wchar_uacter sequence just prior to
     * execution of the <code>append</code> method. Then the wchar_uacter at
     * index <i>k</i> in this wchar_uacter sequence becomes equal to the
     * wchar_uacter at index <i>k</i> in this sequence, if <i>k</i> is less than
     * <i>n</i>; otherwise, it is equal to the wchar_uacter at index 
     * <i>k+start-n</i> in the argument <code>s</code>.
     * <p>
     * If <code>s</code> is <code>null</code>, then this method appends
     * wchar_uacters as if the s parameter was a sequence containing the four
     * wchar_uacters <code>"null"</code>.
     *
     * @param   s the sequence to append.
     * @param   start   the starting index of the subsequence to be appended.
     * @param   end     the end index of the subsequence to be appended.
     * @return  a reference to this object.
     * @throws     IndexOutOfBoundsException if
     *                  <code>start</code> or <code>end</code> are negative, or
     *             <code>start</code> is greater than <code>end</code> or
     *             <code>end</code> is greater than <code>s.length()</code>
     */
    virtual AbstractStringBuilder* append(CharSequence* s, int start, int end);
    virtual AbstractStringBuilder* append(AbstractStringBuilder* sb);

    /**
     * Appends the string representation of the <code>wchar_u</code> array 
     * argument to this sequence. 
     * <p>
     * The wchar_uacters of the array argument are appended, in order, to 
     * the contents of this sequence. The length of this sequence
     * increases by the length of the argument. 
     * <p>
     * The overall effect is exactly as if the argument were converted to 
     * a string by the method {@link String#valueOf(wchar_u[])} and the 
     * wchar_uacters of that string were then {@link #append(String) appended} 
     * to this wchar_uacter sequence.
     *
     * @param   str   the wchar_uacters to be appended.
     * @return  a reference to this object.
     */
    virtual AbstractStringBuilder* append(const char* str);
    virtual AbstractStringBuilder* append(const char* str, int length);
    virtual AbstractStringBuilder* append(const char* str, int offset, int length);
    
    /**
     * Appends the string representation of the <code>wchar_u</code> array 
     * argument to this sequence. 
     * <p>
     * The wchar_uacters of the array argument are appended, in order, to 
     * the contents of this sequence. The length of this sequence
     * increases by the length of the argument. 
     * <p>
     * The overall effect is exactly as if the argument were converted to 
     * a string by the method {@link String#valueOf(wchar_u[])} and the 
     * wchar_uacters of that string were then {@link #append(String) appended} 
     * to this wchar_uacter sequence.
     *
     * @param   str   the wchar_uacters to be appended.
     * @return  a reference to this object.
     */
    virtual AbstractStringBuilder* append(const wchar_t* str);
    virtual AbstractStringBuilder* append(const wchar_t* str, int length);
    virtual AbstractStringBuilder* append(const wchar_t* str, int offset, int length);

    /**
     * Appends the string representation of the <code>wchar_u</code> array 
     * argument to this sequence. 
     * <p>
     * The wchar_uacters of the array argument are appended, in order, to 
     * the contents of this sequence. The length of this sequence
     * increases by the length of the argument. 
     * <p>
     * The overall effect is exactly as if the argument were converted to 
     * a string by the method {@link String#valueOf(wchar_u[])} and the 
     * wchar_uacters of that string were then {@link #append(String) appended} 
     * to this wchar_uacter sequence.
     *
     * @param   str   the wchar_uacters to be appended.
     * @return  a reference to this object.
     */
    virtual AbstractStringBuilder* append(const wchar_u* str);
    virtual AbstractStringBuilder* append(const wchar_u* str, int length);
    virtual AbstractStringBuilder* append(const wchar_u* str, int offset, int length);

    /**
     * Appends the string representation of the <code>bool</code> 
     * argument to the sequence.
     * <p>
     * The argument is converted to a string as if by the method 
     * <code>String.valueOf</code>, and the wchar_uacters of that 
     * string are then appended to this sequence. 
     *
     * @param   b   a <code>bool</code>.
     * @return  a reference to this object.
     */
    virtual AbstractStringBuilder* append(wchar_u c);
    virtual AbstractStringBuilder* append(bool b);
    virtual AbstractStringBuilder* append(int i);
    virtual AbstractStringBuilder* append(dg_long l);
    virtual AbstractStringBuilder* append(float val);
    virtual AbstractStringBuilder* append(double val);

public:

    /**
     * Returns a string representing the data in this sequence.
     * A new <code>String</code> object is allocated and initialized to 
     * contain the wchar_uacter sequence currently represented by this 
     * object. This <code>String</code> is then returned. Subsequent 
     * changes to this sequence do not affect the contents of the 
     * <code>String</code>.
     *
     * @return  a string representation of this sequence of wchar_uacters.
     */
    virtual String* toString() = 0;


protected:
	/**
     * This implements the expansion semantics of ensureCapacity with no
     * size check or synchronization.
     */
	virtual void expandCapacity(int minimumCapacity);

protected:
    /**
     * The value is used for character storage.
     */
	Array<wchar_u> value;

    /** 
     * The count is the number of characters used.
     */
	int count;
	
};//AbstractStringBuilder

EndPackage2 //(dragon, lang)

#endif //AbstractStringBuilder_Lang_Dragon_H
