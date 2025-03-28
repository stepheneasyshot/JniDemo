package com.stephen.jnidemo.functionpage

import androidx.compose.foundation.Image
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.ExperimentalLayoutApi
import androidx.compose.foundation.layout.FlowRow
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.remember
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.asImageBitmap
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.stephen.jnidemo.appContext
import com.stephen.jnitest.ImageBlurUtils
import com.stephen.jnitest.loadBitmapFromAssets

@OptIn(ExperimentalLayoutApi::class)
@Composable
fun ImageBlurPage() {
    FlowRow {
        val javaBlurImage = remember {
            ImageBlurUtils.blurByJava(loadBitmapFromAssets(appContext, "panda.png"), 10, false)
        }
        val cplusNativeBlur = remember {
            ImageBlurUtils.blurNatively(loadBitmapFromAssets(appContext, "panda.png"), 10, false)
        }
        val cplusNativeBlurByPixels = remember {
            ImageBlurUtils.blurNativelyPixels(
                loadBitmapFromAssets(appContext, "panda.png"),
                10,
                false
            )
        }
        Column {
            Text("Java Blur", fontSize = 36.sp, modifier = Modifier.padding(24.dp))
            javaBlurImage?.let {
                Image(
                    bitmap = it.asImageBitmap(),
                    contentDescription = "1 Blur",
                    modifier = Modifier.size(400.dp, 200.dp)
                )
            }
        }
        Column {
            Text("C++ blurNatively", fontSize = 36.sp, modifier = Modifier.padding(24.dp))
            cplusNativeBlur?.let {
                Image(
                    bitmap = it.asImageBitmap(),
                    contentDescription = "2 Blur",
                    modifier = Modifier.size(400.dp, 200.dp)
                )
            }
        }
       Column {
           Text("C++ blurNativelyPixels", fontSize = 36.sp, modifier = Modifier.padding(24.dp))
           cplusNativeBlurByPixels?.let {
               Image(
                   bitmap = it.asImageBitmap(),
                   contentDescription = "3 Blur",
                   modifier = Modifier.size(400.dp, 200.dp)
               )
           }
       }
    }
}