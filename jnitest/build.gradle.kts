import java.text.SimpleDateFormat
import java.util.Date

plugins {
    id("com.android.library")
    id("org.jetbrains.kotlin.android")
}

fun releaseTime(): String = SimpleDateFormat("yyyyMMdd").format(Date())

android {
    namespace = "com.stephen.jnitest"
    compileSdk = 34

    defaultConfig {
        minSdk = 31

        version = "1.0.0"

        testInstrumentationRunner = "androidx.test.runner.AndroidJUnitRunner"
        consumerProguardFiles("consumer-rules.pro")
    }

    buildTypes {
        release {
            isMinifyEnabled = true
            proguardFiles(
                getDefaultProguardFile("proguard-android-optimize.txt"),
                "proguard-rules.pro"
            )
        }
    }

    externalNativeBuild {
        cmake {
            path = file("src/main/cpp/CMakeLists.txt")
        }
    }

    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_11
        targetCompatibility = JavaVersion.VERSION_11
    }
    kotlinOptions {
        jvmTarget = "11"
    }

    val appName = "JniTest"
    android.libraryVariants.configureEach {
        outputs.all {
            if (this is com.android.build.gradle.internal.api.LibraryVariantOutputImpl) {
                this.outputFileName =
                    "${appName}_V${releaseTime()}.aar"
            }
        }
    }
}

dependencies {
    implementation("androidx.core:core-ktx:1.13.1")
    implementation("androidx.appcompat:appcompat:1.7.0")
    implementation("com.google.android.material:material:1.12.0")
    testImplementation("junit:junit:4.13.2")
    androidTestImplementation("androidx.test.ext:junit:1.2.1")
    androidTestImplementation("androidx.test.espresso:espresso-core:3.6.1")
}