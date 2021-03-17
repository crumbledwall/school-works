<template>
  <div class="main">
    <el-card class="main-card">
      <div id="wb" />
      <div id="tb" />
    </el-card>
    <div class="content">
      <div ref="large" class="main-window" />
      <div ref="small" class="sub-window" />
      <el-button
        class="change"
        type="primary"
        size="default"
        plain
        @click="change"
      >切换屏幕共享</el-button>
    </div>
    <el-card
      class="msg-card"
    ><div class="msg-show" />
      <div class="form">
        <el-input v-model="input" class="input" placeholder="请输入内容" />
        <el-button type="primary" size="default" @click="test">发送</el-button>
      </div>
    </el-card>
  </div>
</template>

<script>
import NIM from '@/sdk/NIM_Web_NIM_v7.1.0.js'
import WebRTC2 from '@/sdk/NIM_Web_WebRTC2_v3.7.0.js'
import * as Chatroom from '@/sdk/NIM_Web_Chatroom_v7.1.1.js'
import WhiteBoard from '@/sdk/NIM_Web_WhiteBoard_v7.1.0.js'
import * as DrawPlugin from '@/sdk/DrawPlugin.2.0.0.js'
import * as DrawPluginUI from '@/sdk/DrawPluginUI.2.0.0.js'
import Cookies from 'js-cookie'
import axios from 'axios'
import JsSha from 'jssha'

export default {
  name: 'WhiteBoard',
  data() {
    return {
      input: '',
      tokensave: '',
      message: '',
      account: '',
      isSilence: false,
      isDesc: true,
      isStop: false,
      screenval: false,
      desc: '等待对方进入...',
      client: null,
      localUid: Math.ceil(Math.random() * 1e5),
      localStream: null,
      remoteStream: null
    }
  },
  mounted() {
    window.message = this.message
    var whiteboard
    NIM.use(WhiteBoard)

    var handler

    const identity = Cookies.get('identity')
    const account = Cookies.get('account')
    const channelName = Cookies.get('room')

    // 初始化NIM，为了兼容老版本，录制回放的播放图片PPT的时候需要用nim去获取文件
    var nim = NIM.getInstance({
      db: false,
      debug: false, // param.debug,
      appKey: '01c3c8df2e99ef4ae847a959f6a1bac1',
      account: account,

      token: Cookies.get('token'),
      onconnect: function(event) {
        initWB()
        console.log(nim)
      },
      onerror: function(event) {
        console.error('im onerror:', event)
        // onNativeFunction('webError', {
        //   code: 400,
        //   msg: event.message || 'im onerror 网络状态异常'
        // })
      },
      onwillreconnect: function(event) {
        console.log('im onwillreconnect:', event)
        // onNativeFunction('webReconnect')
      },
      ondisconnect: function(error) {
        switch (error.code) {
          case 302:
            break
          case 'kicked':
            break
          default:
        }
        // onNativeFunction('webLoginIMFailed', {
        //   code: error.code,
        //   msg: msg || error.message || '连接断开'
        // })
        nim.destroy()
      }
    })

    function initWB() {
      whiteboard = WhiteBoard.getInstance({
        nim: nim,
        debug: false
      })
      window.whiteboard = whiteboard
      joinChannel()
    }

    function joinChannel() {
      whiteboard
        .joinChannel({
          channelName: channelName, // /initParam.channelName,
          sessionConfig: {
            record: false // initParam.record // background 。。。
          }
        })
        .then(function(obj) {
          console.log('whiteboard::joinChannel success', obj)
          whiteboard.startSession().then(function() {
            onWBInited()
          })
        })
        .catch(function(err) {
          console.error('whiteboard::joinChannel failed', err)
          if (
            err &&
            err.event &&
            err.event.code === 404 &&
            identity === 'owner'
          ) {
            // 已创建房间
            createChannel()
            return
          }

          whiteboard.leaveChannel()
        })
    }

    function createChannel() {
      whiteboard
        .createChannel({
          channelName: channelName
        })
        .then(function(obj) {
          console.log('whiteboard::createChannel success', obj)
          joinChannel()
        })
        .catch(function(err) {
          console.error('whiteboard::createChannel failed', err)
          if (err && err.event && err.event.code === 417) {
            // 已创建房间
            joinChannel()
          } else {
            whiteboard.leaveChannel()
          }
        })
    }

    function onWBInited() {
      // onNativeFunction('webJoinWBSucceed') // 通知 native 加入房间成功
      // if (toolbar) return
      console.log('onWBInited')
      handler = DrawPlugin.getInstance({
        debug: false,
        width: 200,
        height: 200,
        account: account,
        ownerAccount: account,
        identity: identity, // 默认成员 'normal'
        appKey: '01c3c8df2e99ef4ae847a959f6a1bac1',

        whiteboardContainer: document.getElementById('wb'),
        nim: nim,
        whiteboard: whiteboard
      })
      handler.on('customEvent', function(event) {
        if (event === 'selectDoc') {
          // 一般是弹出界面，让用户选择使用那个文件
          // 这里是自定义传入一个文档图片，所以使用的是setFileObjRaw,如果是使用nim转码的文档，请使用setFileObj
          handler.setFileObjRaw({
            currentPage: 1,
            docId: 'c83e6ff4-297e-4fc3-b0c0-a0294776cb12',
            type: 'img',
            pageCount: '13',
            url:
              'http://nim.nosdn.127.net/60a9143c-146d-42f0-b55e-d8009dadc9e4_2_1.jpg',
            urlStr:
              'http://nim.nosdn.127.net/60a9143c-146d-42f0-b55e-d8009dadc9e4_2_{index}.jpg'
          })
        } else if (event === 'closeDoc') {
          handler.clearFile()
        }
      })
      handler.on('inited', function() {
        // 必须调用这个去同步数据，在断线重连之后，也需要重新去同步
        handler.readyToSyncData()

        handler.enableDraw(true)
        handler.setSize(8)
        handler.setTool('flag') // 使用自由画笔工具，
        DrawPluginUI.mount(
          document.getElementById('tb'),
          { account, identity },
          handler,
          {
            toolbar: [
              'flag',
              'free',
              'text',
              'fill',
              { type: 'shapes', items: ['line', 'rect', 'circle'] },
              { type: 'formats', fontsize: [23, 30, 44] },
              'erase',
              'undo',
              'redo',
              'clear',
              { type: 'customTXT', label: '文档库', eventName: 'selectDoc' }
            ]
          }
        )
      })

      window.handler = handler
      var isReconnecting
      whiteboard.on('connected', () => {
        // 如果断线重连之后，重新连上，
        if (isReconnecting) {
          isReconnecting = false
          if (this.drawPlugin) {
            this.drawPlugin.readyToSyncData()
          }
        }
      })

      whiteboard.on('willReconnect', () => {
        // 标记重连
        isReconnecting = true
      })

      /**
       * RecordPlayerUI
       */
      whiteboard.on('error', function(err) {
        // 非正常情况处理
        console.error('whiteboard onError:', err)
        // onNativeFunction('webError', {
        //   code: 400,
        //   msg: err.message || 'whiteboard onerror 网络状态异常'
        // })
      })
      whiteboard.on('signalClosed', function(obj) {
        console.error('whiteboard signalClosed:', obj)
        // onNativeFunction('webError', {
        //   code: 400,
        //   msg: 'whiteboard signal closed 网络状态异常'
        // })
      })
    }

    console.warn('初始化音视频sdk')
    window.self = this
    this.client = WebRTC2.createClient({
      appkey: '01c3c8df2e99ef4ae847a959f6a1bac1',
      debug: false
    })
    // 监听事件
    this.client.on('peer-online', evt => {
      console.warn(`${evt.uid} 加入房间`)
    })

    this.client.on('peer-leave', evt => {
      console.warn(`${evt.uid} 离开房间`)
      if (this.remoteStream.getId() === evt.uid) {
        this.remoteStream = null
        this.isDesc = true
        this.desc = '对方离开房间了'
        // message(this.desc)
      }
    })

    this.client.on('stream-added', evt => {
      var remoteStream = evt.stream
      console.warn('收到对方发布的订阅消息: ', remoteStream.getId())

      this.remoteStream = remoteStream

      this.subscribe(remoteStream)
    })

    this.client.on('stream-removed', evt => {
      var remoteStream = evt.stream
      console.warn('对方停止订阅: ', remoteStream.getId())
      remoteStream.stop()
    })

    this.client.on('stream-subscribed', evt => {
      console.warn('收到了对端的流，准备播放')
      const remoteStream = evt.stream
      // 用于播放对方视频画面的div节点
      this.isDesc = false
      const div = this.$refs.small
      remoteStream
        .play(div)
        .then(() => {
          console.warn('播放视频')
          remoteStream.setRemoteRenderMode({
            // 设置视频窗口大小
            width: 250,
            height: 200,
            cut: true // 是否裁剪
          })
        })
        .catch(err => {
          console.warn('播放对方视频失败了: ', err)
        })
    })
    this.getToken(
      '01c3c8df2e99ef4ae847a959f6a1bac1',
      this.localUid,
      '132737698f0a'
    )
      .then(token => {
        this.tokensave = token
        this.joinChannel2(token, this.screenval)
      })
      .catch(e => {
        // message(e)
        console.error(e)
      })

    var chatroom = Chatroom.getInstance({
      appKey: '01c3c8df2e99ef4ae847a959f6a1bac1',
      account: Cookies.get('account'),
      token: Cookies.get('token'),
      chatroomId: '334743222',
      chatroomAddresses: [
        'chatweblink10.netease.im:443',
        'chatweblink04.netease.im:443'
      ],
      onconnect: onChatroomConnect,
      onerror: onChatroomError,
      onwillreconnect: onChatroomWillReconnect,
      ondisconnect: onChatroomDisconnect,
      // 消息
      onmsgs: onChatroomMsgs
    })
    function onChatroomConnect(obj) {
      console.log('进入聊天室', obj)
    }
    function onChatroomWillReconnect(obj) {
      // 此时说明 `SDK` 已经断开连接, 请开发者在界面上提示用户连接已断开, 而且正在重新建立连接
      console.log('即将重连', obj)
    }
    function onChatroomDisconnect(error) {
      // 此时说明 `SDK` 处于断开状态, 开发者此时应该根据错误码提示相应的错误信息, 并且跳转到登录页面
      console.log('连接断开', error)
      if (error) {
        switch (error.code) {
          // 账号或者密码错误, 请跳转到登录页面并提示错误
          case 302:
            break
          // 被踢, 请提示错误后跳转到登录页面
          case 'kicked':
            break
          default:
            break
        }
      }
    }
    function onChatroomError(error, obj) {
      console.log('发生错误', error, obj)
    }
    function onChatroomMsgs(msgs) {
      msgs.map(msg => {
        document.getElementsByClassName(
          'msg-show'
        )[0].innerHTML = document
          .getElementsByClassName('msg-show')[0]
          .innerHTML.concat(`<div class="msg">${msg.text}</div>`)
      })
      document
      console.log('收到聊天室消息', msgs)
    }

    window.chatroom = chatroom
  },
  methods: {
    change() {
      console.log('change')
      this.client.leave()
      this.screenval = !this.screenval
      this.joinChannel2(this.tokensave, this.screenval)
    },
    test() {
      window.chatroom.sendText({
        text: this.input,
        done: (err, msgObj) => {
          console.log(err, msgObj)
          document.getElementsByClassName(
            'msg-show'
          )[0].innerHTML = document
            .getElementsByClassName('msg-show')[0]
            .innerHTML.concat(`<div class="msg">${this.input}</div>`)
          this.input = ''
        }
      })

      window.chatroom.getHistoryMsgs({
        timetag: 1451,
        limit: 100,
        msgTypes: ['text', 'image'],
        done: (err, obj) => {
          console.log(obj.msgs, err)
        }
      })
    },
    getToken(appkey, uid, appSecret) {
      const getTokenUrl =
        'https://api.netease.im/nimserver/user/getToken.action'
      const Nonce = Math.ceil(Math.random() * 1e9)
      const CurTime = Math.ceil(Date.now() / 1000)
      const aaa = `${appSecret}${Nonce}${CurTime}`
      const sha1 = new JsSha('SHA-1', 'TEXT', { encoding: 'UTF8' })
      sha1.update(aaa)
      const CheckSum = sha1.getHash('HEX')
      return new Promise((resolve, reject) => {
        axios
          .post(getTokenUrl, `uid=${uid}`, {
            headers: {
              'Content-Type': 'application/x-www-form-urlencoded;charset=utf-8',
              AppKey: appkey,
              Nonce,
              CurTime,
              CheckSum
            }
          })
          .then(function(data) {
            var d = data.data
            if (d.code !== 200) {
              reject(new Error('getChecksum code: ' + d.code))
              return
            }
            resolve(d.token)
          })
          .catch(error => {
            reject(new Error('getChecksum error: ', error))
          })
      })
    },
    returnJoin(time = 2000) {
      setTimeout(() => {
        this.$router.push({
          path: '/'
        })
      }, time)
    },
    joinChannel2(token, screen) {
      if (!this.client) {
        // message('内部错误，请重新加入房间')
        return
      }
      console.info('开始加入房间: ', Cookies.get('room'))
      this.client
        .join({
          channelName: Cookies.get('room'),
          uid: this.localUid,
          token
        })
        .then(data => {
          console.info('加入房间成功，开始初始化本地音视频流')
          this.initLocalStream(screen)
        })
        .catch(error => {
          console.error('加入房间失败：', error)
          // message(`${error}: 请检查appkey或者token是否正确`)
          // this.returnJoin()
        })
    },
    initLocalStream(screen) {
      // 初始化本地的Stream实例，用于管理本端的音视频流
      this.localStream = WebRTC2.createStream({
        uid: this.localUid,
        audio: true, // 是否启动mic
        video: !screen, // 是否启动camera
        screen: screen // 是否启动屏幕共享
      })

      // 设置本地视频质量
      this.localStream.setVideoProfile({
        resolution: WebRTC2.VIDEO_QUALITY_720p, // 设置视频分辨率
        frameRate: WebRTC2.CHAT_VIDEO_FRAME_RATE_60 // 设置视频帧率
      })
      // 设置本地音频质量
      this.localStream.setAudioProfile('speech_low_quality')
      // 启动媒体，打开实例对象中设置的媒体设备
      this.localStream
        .init()
        .then(() => {
          console.warn('音视频开启完成，可以播放了')
          const div = self.$refs.large
          this.localStream.play(div)
          this.localStream.setLocalRenderMode({
            // 设置视频窗口大小
            width: 250,
            height: 200,
            cut: true // 是否裁剪
          })
          // 发布
          this.publish()
        })
        .catch(err => {
          console.warn('音视频初始化失败: ', err)
          // message('音视频初始化失败')
          this.localStream = null
        })
    },
    publish() {
      console.warn('开始发布视频流')
      // 发布本地媒体给房间对端
      this.client
        .publish(this.localStream)
        .then(() => {
          console.warn('本地 publish 成功')
        })
        .catch(err => {
          console.error('本地 publish 失败: ', err)
          // message('本地 publish 失败')
        })
    },
    subscribe() {
      this.remoteStream.setSubscribeConfig({
        audio: true,
        video: true
      })
      this.client
        .subscribe(this.remoteStream)
        .then(() => {
          console.warn('本地 subscribe 成功')
        })
        .catch(err => {
          console.warn('本地 subscribe 失败: ', err)
          // message('订阅对方的流失败')
        })
    },
    setOrRelieveSilence() {
      const { isSilence } = this
      this.isSilence = !isSilence
      if (this.isSilence) {
        console.warn('关闭mic')
        this.localStream
          .close({
            type: 'audio'
          })
          .then(() => {
            console.warn('关闭 mic sucess')
          })
          .catch(err => {
            console.warn('关闭 mic 失败: ', err)
            // message('关闭 mic 失败')
          })
      } else {
        console.warn('打开mic')
        if (!this.localStream) {
          // message('当前不能打开mic')
          return
        }
        this.localStream
          .open({
            type: 'audio'
          })
          .then(() => {
            console.warn('打开mic sucess')
          })
          .catch(err => {
            console.warn('打开mic失败: ', err)
            // message('打开mic失败')
          })
      }
    },
    stopOrOpenVideo() {
      const { isStop } = this
      this.isStop = !isStop
      if (this.isStop) {
        console.warn('关闭摄像头')
        this.localStream
          .close({
            type: 'video'
          })
          .then(() => {
            console.warn('关闭摄像头 sucess')
          })
          .catch(err => {
            console.warn('关闭摄像头失败: ', err)
            // message('关闭摄像头失败')
          })
      } else {
        console.warn('打开摄像头')
        if (!this.localStream) {
          // message('当前不能打开camera')
          return
        }
        this.localStream
          .open({
            type: 'video'
          })
          .then(() => {
            console.warn('打开摄像头 sucess')
            const div = self.$refs.large
            this.localStream.play(div)
            this.localStream.setLocalRenderMode({
              // 设置视频窗口大小
              width: div.clientWidth,
              height: div.clientHeight,
              cut: true // 是否裁剪
            })
          })
          .catch(err => {
            console.warn('打开摄像头失败: ', err)
            // message('打开摄像头失败')
          })
      }
    },
    handleOver() {
      console.warn('离开房间')
      this.client.leave()
      // this.returnJoin(1)
    }
  }
}
</script>

<style scope>
html,
body {
  margin: 0;
  padding: 0;
  height: 100%;
  width: 100%;
}

.main-card /deep/ .el-card__body {
  height: 400px;
  width: 500px;
}
.main-card {
  width: 500px;
  margin-right: 50px;
}

canvas {
  /* image-rendering: optimizeSpeed; */
  image-rendering: pixelated;
  image-rendering: -moz-crisp-edges;
  image-rendering: -webkit-optimize-contrast;
  image-rendering: optimize-contrast;
  -ms-interpolation-mode: nearest-neighbor;
  transform: translate3d(0, 0, 0);
}

#app {
  /* position: fixed !important; */
  top: 0;
  right: 0;
  bottom: 0;
  left: 0;
}

#wb {
  top: 0;
  right: 0;
  bottom: 0;
  left: 0;
  height: 100%;
  background: #eeeeee;
}

canvas:first-child {
  left: 0 !important;
}
#tb {
  left: 0;
  bottom: 30px;
  position: relative;
  width: 100%;
  height: 46px;
  z-index: 999;
  pointer-events: none;
}

#js-video {
  position: absolute;
  top: 0;
  right: 0;
  width: 400px;
  height: 300px;
}

input::placeholder,
input::-webkit-input-placeholder,
input::-moz-placeholder {
  line-height: normal !important;
}

.main-window {
  height: 200px;
  width: 300px;
  background: #000;
}
.sub-window {
  height: 200px;
  width: 300px;
  background: #000;
}
.main {
  display: flex;
  flex-direction: row;
  align-items: center;
  justify-content: center;
  height: 100vh;
}
.msg-card {
  width: 300px;
  height: 400px;
  margin-left: 50px;
}

.msg-card /deep/ .el-card__body {
  height: 400px;
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-items: center;
}

.form {
  display: flex;
}
.input {
  margin-right: 5px;
}
.msg-show {
  height: 450px;
  word-break: break-all;
  width: 300px;
  overflow: auto;
  text-align: left;
  padding-left: 40px;
}
.change{
  margin-top: 30px;
}
</style>
