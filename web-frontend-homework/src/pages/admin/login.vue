<template>
  <div class="login-container">
    <div class="login-form-container">
      <h1>图片管理系统</h1>
      <el-form>
        <el-input
          id="username"
          v-model="LoginForm.username"
          placeholder="请输入用户名"
          size="large"
        >
        </el-input>
        <br />
        <br />
        <el-input
          id="password"
          type="password"
          v-model="LoginForm.passwd"
          placeholder="请输入密码"
          size="large"
        >
        </el-input>
        <br />
        <div class="login-register">
          <a href="#/register">没有帐号？快去注册！</a>
        </div>
        <el-button round class="login-submit" type="primary" @click="Login"
          >登 录</el-button
        >
      </el-form>
    </div>
  </div>
</template>

<script>

export default {
  metaInfo: {
    title: 'Login'
  },
  data () {
    return {
      LoginForm: {
        username: '',
        passwd: ''
      }
    }
  },
  created () {
    this.check()
  },
  methods: {
    check: function () {
      var cookie = this.$cookies.get('login')
      if (cookie) {
        alert("You've loged in!")
        this.$router.push({ path: '/' })
      }
    },
    Login: function () {
      if (this.LoginForm.username.length <= 10) {
        alert("too short!")
        return
      }
      if (this.LoginForm.passwd.length <= 10) {
        alert("too short!")
        return
      }
      this.$cookies.set("login", "true")
      this.check()
    }
  },
  components: {
  }
}
</script>

<style scoped>
.login-container {
  font-family: "Avenir", Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #409eff;
  width: 100%;
  height: 100%;
  position: fixed;
}
.login-form-container {
  width: 25%;
  margin: 10% 37.5%;
}
.login-submit {
  width: 100%;
  font-size: 15px;
}
.login-register {
  text-align: right;
  margin: 3px 3px;
  font-size: 15px;
}
a {
  text-decoration: none;
  color: #409eff;
}
.el-input >>> .el-input__inner {
  padding-left: 36px;
}
</style>
