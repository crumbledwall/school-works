<template>
  <div class="login">
    <el-card>
      <h2>Login</h2>
      <el-form
        ref="form"
        class="login-form"
        :model="model"
        :rules="rules"
        @submit.prevent="login"
      >
        <el-form-item prop="email">
          <el-input v-model="model.email" placeholder="email" prefix-icon="fas fa-user" />
        </el-form-item>
        <el-form-item prop="password">
          <el-input
            v-model="model.password"
            placeholder="Password"
            type="password"
            prefix-icon="fas fa-lock"
          />
        </el-form-item>
        <el-form-item>
          <el-button
            :loading="loading"
            class="login-button"
            type="primary"
            native-type="submit"
            block
          >Login</el-button>
        </el-form-item>

      </el-form>
    </el-card>
  </div>
</template>

<script>
export default {
  name: 'Login',
  data() {
    return {
      validCredentials: {
        email: 'lightscope',
        password: 'lightscope'
      },
      model: {
        email: '',
        password: ''
      },
      loading: false,
      rules: {
        email: [
          {
            required: true,
            message: 'email is required',
            trigger: 'blur'
          },
          {
            min: 4,
            message: 'email length should be at least 5 characters',
            trigger: 'blur'
          }
        ],
        password: [
          { required: true, message: 'Password is required', trigger: 'blur' },
          {
            min: 5,
            message: 'Password length should be at least 5 characters',
            trigger: 'blur'
          }
        ]
      }
    }
  },
  methods: {
    login() {
      this.$refs['form'].validate((valid) => {
        if (valid) {
          this.loading = true
          this.$store.dispatch('user/login', this.model).then((res) => {
            this.$router.push({ path: '/' })
          })
          this.loading = false
        } else {
          console.log('error submit!!')
          return false
        }
      })
    }
  }
}
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
.login {
  flex: 1;
  display: flex;
  justify-content: center;
  align-items: center;
}

.login-button {
  width: 100%;
  margin-top: 40px;
}
.login-form {
  width: 290px;
}
.forgot-password {
  margin-top: 10px;
}

.login .el-input__prefix {
  background: rgb(238, 237, 234);
  left: 0;
  height: calc(100% - 2px);
  left: 1px;
  top: 1px;
  border-radius: 3px;
}
.login .el-input input {
  padding-left: 35px;
}
.login .el-card {
  padding-top: 0;
  padding-bottom: 30px;
}
h2 {
  font-family: "Open Sans";
  letter-spacing: 1px;
  font-family: Roboto, sans-serif;
  padding-bottom: 20px;
}

.login .el-card {
  width: 340px;
  display: flex;
  justify-content: center;
}
</style>
