package com.stephen.jnitest

import android.content.Context
import android.graphics.Bitmap
import android.graphics.BitmapFactory
import java.io.IOException
import kotlin.math.abs
import kotlin.math.max
import kotlin.math.min

object ImageBlurUtils {
    /**
     * Init JNI
     */
    fun init() {
        System.loadLibrary("image-blur")
    }

    /**
     * Blur Image By Pixels
     *
     * @param img Img pixel array
     * @param w   Img width
     * @param h   Img height
     * @param r   Blur radius
     */
    private external fun blurPixels(img: IntArray, w: Int, h: Int, radius: Int)

    /**
     * Blur Image By Bitmap
     *
     * @param bitmap Img Bitmap
     * @param r      Blur radius
     */
    private external fun blurBitmap(bitmap: Bitmap, r: Int)

    private fun buildBitmap(original: Bitmap?, canReuseInBitmap: Boolean): Bitmap {
        val config = original?.getConfig()
        if (config != Bitmap.Config.ARGB_8888 && config != Bitmap.Config.RGB_565) {
            throw RuntimeException("Blur bitmap only supported Bitmap.Config.ARGB_8888 and Bitmap.Config.RGB_565.")
        }
        // If can reuse in bitmap return this or copy
        val rBitmap = if (canReuseInBitmap) original
        else original.copy(config, true)
        return (rBitmap)
    }

    /**
     * StackBlur By Jni Bitmap
     *
     * @param original         Original Image
     * @param radius           Blur radius
     * @param canReuseInBitmap Can reuse In original Bitmap
     * @return Image Bitmap
     */
    fun blurNatively(original: Bitmap?, radius: Int, canReuseInBitmap: Boolean): Bitmap? {
        if (radius < 1) {
            throw Exception("radius cant be less than 1")
        }
        val bitmap = buildBitmap(original, canReuseInBitmap)
        // Return this none blur
        if (radius == 1) {
            return bitmap
        }
        //Jni BitMap Blur
        blurBitmap(bitmap, radius)

        return (bitmap)
    }

    /**
     * StackBlur By Jni Pixels
     *
     * @param original         Original Image
     * @param radius           Blur radius
     * @param canReuseInBitmap Can reuse In original Bitmap
     * @return Image Bitmap
     */
    fun blurNativelyPixels(original: Bitmap?, radius: Int, canReuseInBitmap: Boolean): Bitmap? {
        if (radius < 1) {
            throw Exception("radius cant be less than 1")
        }
        val bitmap = buildBitmap(original, canReuseInBitmap)
        // Return this none blur
        if (radius == 1) {
            return bitmap
        }
        val w = bitmap.getWidth()
        val h = bitmap.getHeight()
        val pix = IntArray(w * h)
        bitmap.getPixels(pix, 0, w, 0, 0, w, h)
        // Jni Pixels Blur
        blurPixels(pix, w, h, radius)
        bitmap.setPixels(pix, 0, w, 0, 0, w, h)
        return (bitmap)
    }


    /**
     * StackBlur By Java Bitmap
     *
     * @param original         Original Image
     * @param radius           Blur radius
     * @param canReuseInBitmap Can reuse In original Bitmap
     * @return Image Bitmap
     */
    fun blurByJava(original: Bitmap?, radius: Int, canReuseInBitmap: Boolean): Bitmap? {
        if (radius < 1) {
            return (null)
        }
        val bitmap: Bitmap = buildBitmap(original, canReuseInBitmap)

        // Return this none blur
        if (radius == 1) {
            return bitmap
        }

        val w = bitmap.getWidth()
        val h = bitmap.getHeight()

        val pix = IntArray(w * h)
        // get array
        bitmap.getPixels(pix, 0, w, 0, 0, w, h)

        // run Blur
        val wm = w - 1
        val hm = h - 1
        val wh = w * h
        val div = radius + radius + 1

        val r: ShortArray? = ShortArray(wh)
        val g: ShortArray? = ShortArray(wh)
        val b: ShortArray? = ShortArray(wh)
        var rSum: Int
        var gSum: Int
        var bSum: Int
        var x: Int
        var y: Int
        var i: Int
        var p: Int
        var yp: Int
        var yi: Int
        var yw: Int
        val vMin: IntArray? = IntArray(max(w, h))

        var divSum = (div + 1) shr 1
        divSum *= divSum

        val dv: ShortArray? = ShortArray(256 * divSum)
        i = 0
        while (i < 256 * divSum) {
            dv!![i] = (i / divSum).toShort()
            i++
        }

        yi = 0
        yw = yi

        val stack: Array<IntArray> = Array<IntArray?>(div) { IntArray(3) } as Array<IntArray>
        var stackPointer: Int
        var stackStart: Int
        var sir: IntArray
        var rbs: Int
        val r1 = radius + 1
        var routSum: Int
        var goutSum: Int
        var boutSum: Int
        var rinSum: Int
        var ginSum: Int
        var binSum: Int

        y = 0
        while (y < h) {
            bSum = 0
            gSum = bSum
            rSum = gSum
            boutSum = rSum
            goutSum = boutSum
            routSum = goutSum
            binSum = routSum
            ginSum = binSum
            rinSum = ginSum
            i = -radius
            while (i <= radius) {
                p = pix[yi + min(wm, max(i, 0))]
                sir = stack[i + radius]
                sir[0] = (p and 0xff0000) shr 16
                sir[1] = (p and 0x00ff00) shr 8
                sir[2] = (p and 0x0000ff)

                rbs = r1 - abs(i)
                rSum += sir[0] * rbs
                gSum += sir[1] * rbs
                bSum += sir[2] * rbs
                if (i > 0) {
                    rinSum += sir[0]
                    ginSum += sir[1]
                    binSum += sir[2]
                } else {
                    routSum += sir[0]
                    goutSum += sir[1]
                    boutSum += sir[2]
                }
                i++
            }
            stackPointer = radius

            x = 0
            while (x < w) {
                r!![yi] = dv!![rSum]
                g!![yi] = dv[gSum]
                b!![yi] = dv[bSum]

                rSum -= routSum
                gSum -= goutSum
                bSum -= boutSum

                stackStart = stackPointer - radius + div
                sir = stack[stackStart % div]

                routSum -= sir[0]
                goutSum -= sir[1]
                boutSum -= sir[2]

                if (y == 0) {
                    vMin!![x] = min((x + radius + 1), wm)
                }
                p = pix[yw + vMin!![x]]

                sir[0] = (p and 0xff0000) shr 16
                sir[1] = (p and 0x00ff00) shr 8
                sir[2] = (p and 0x0000ff)

                rinSum += sir[0]
                ginSum += sir[1]
                binSum += sir[2]

                rSum += rinSum
                gSum += ginSum
                bSum += binSum

                stackPointer = (stackPointer + 1) % div
                sir = stack[(stackPointer) % div]

                routSum += sir[0]
                goutSum += sir[1]
                boutSum += sir[2]

                rinSum -= sir[0]
                ginSum -= sir[1]
                binSum -= sir[2]

                yi++
                x++
            }
            yw += w
            y++
        }
        x = 0
        while (x < w) {
            bSum = 0
            gSum = bSum
            rSum = gSum
            boutSum = rSum
            goutSum = boutSum
            routSum = goutSum
            binSum = routSum
            ginSum = binSum
            rinSum = ginSum
            yp = -radius * w
            i = -radius
            while (i <= radius) {
                yi = max(0, yp) + x

                sir = stack[i + radius]

                sir[0] = r!![yi].toInt()
                sir[1] = g!![yi].toInt()
                sir[2] = b!![yi].toInt()

                rbs = r1 - abs(i)

                rSum += r[yi] * rbs
                gSum += g[yi] * rbs
                bSum += b[yi] * rbs

                if (i > 0) {
                    rinSum += sir[0]
                    ginSum += sir[1]
                    binSum += sir[2]
                } else {
                    routSum += sir[0]
                    goutSum += sir[1]
                    boutSum += sir[2]
                }

                if (i < hm) {
                    yp += w
                }
                i++
            }
            yi = x
            stackPointer = radius
            y = 0
            while (y < h) {
                // Preserve alpha channel: ( 0xff000000 & pix[yi] )
                pix[yi] =
                    (-0x1000000 and pix[yi]) or (dv!![rSum].toInt() shl 16) or (dv[gSum].toInt() shl 8) or dv[bSum].toInt()

                rSum -= routSum
                gSum -= goutSum
                bSum -= boutSum

                stackStart = stackPointer - radius + div
                sir = stack[stackStart % div]

                routSum -= sir[0]
                goutSum -= sir[1]
                boutSum -= sir[2]

                if (x == 0) {
                    vMin!![y] = min((y + r1), hm) * w
                }
                p = x + vMin!![y]

                sir[0] = r!![p].toInt()
                sir[1] = g!![p].toInt()
                sir[2] = b!![p].toInt()

                rinSum += sir[0]
                ginSum += sir[1]
                binSum += sir[2]

                rSum += rinSum
                gSum += ginSum
                bSum += binSum

                stackPointer = (stackPointer + 1) % div
                sir = stack[stackPointer]

                routSum += sir[0]
                goutSum += sir[1]
                boutSum += sir[2]

                rinSum -= sir[0]
                ginSum -= sir[1]
                binSum -= sir[2]

                yi += w
                y++
            }
            x++
        }

        // set Bitmap
        bitmap.setPixels(pix, 0, w, 0, 0, w, h)

        return (bitmap)
    }

}

fun loadBitmapFromAssets(context: Context, fileName: String): Bitmap? {
    val assetManager = context.assets
    val inputStream = assetManager.open(fileName)
    try {
        return BitmapFactory.decodeStream(inputStream)
    } catch (e: IOException) {
        e.printStackTrace()
    } finally {
        try {
            inputStream.close()
        } catch (e: IOException) {
            e.printStackTrace()
        }
    }
    return null
}